#include "../../header/screen/SelectMenu.h"
#include <conio.h>
#include <cstdlib> // 添加 exit 函数头文件
#include <iostream>
#include <utility>
#include <windows.h>
#include "../../header/data/info/Message.h"

std::string SelectMenu::getSpaces(int count) {
    std::string res;
    while (count--)
        res += " ";
    return res;
}

void SelectMenu::monitorKeyEvent() {
    int key = _getch();
    switch (key) {
        case 72: // 上箭头
            updatePointer(-1);
            break;
        case 80: // 下箭头
            updatePointer(1);
            break;
        case 13: // 回车键
            onSelection();
            system("cls");
            updateMenu();
            break;
        case 27: // ESC键
            this->isRunning = false;
            break;
        default:
            break;
    }
}

void SelectMenu::updatePointer(int direction) {
    lastPointer = pointer;
    int index = pointer + direction;
    if (index < 0) {
        pointer = optionList.size() - 1;
    } else if (index >= optionList.size()) {
        pointer = 0;
    } else {
        pointer = index;
    }
}

std::vector<Option> SelectMenu::getOptionList() { return this->optionList; }

Text SelectMenu::getTitle() { return this->title; }

void SelectMenu::setTitle(Text &title) { this->title = std::move(title); }

void SelectMenu::setOptionList(std::vector<Option> &optionList) { this->optionList = std::move(optionList); }

SelectMenu::SelectMenu(const Text &title, std::vector<Option> optionList, std::string pointerColorCode,
                       int optionIndentSpaces, int titleLine) :
    title(title), optionList(std::move(optionList)), titleLine(titleLine), optionIndentSpaces(optionIndentSpaces),
    pointerColorCode(std::move(pointerColorCode)) {
    init();
}

void SelectMenu::init() {
    this->isRunning = true;
    this->pointer = 0;
    this->lastPointer = 0;
}

void SelectMenu::mainLoop() {
    hideCursor();
    updateMenu();
    while (isRunning) {
        monitorKeyEvent();
        if (lastPointer != pointer) {
            updateOptionLine(lastPointer);
            updateOptionLine(pointer);
            lastPointer = pointer;
        }
    }
    showCursor();
}
void SelectMenu::updateOptionLine(int index) {
    if (index < 0 || index >= optionList.size())
        return;

    // 定位到选项行
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = static_cast<SHORT>(optionIndentSpaces);
    position.Y = static_cast<SHORT>(titleLine + index); // 假设标题占2行

    SetConsoleCursorPosition(hConsole, position);

    Option option = optionList[index];
    std::string optionText = option.getContent().getContent();
    std::string displayContent;
    if (index == pointer) {
        displayContent = "$" + pointerColorCode + ">" + "$" + option.getColorCode() + optionText;
    } else {
        displayContent = " " + optionText;
    }
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.dwSize.X;
    int clearWidth = consoleWidth - optionIndentSpaces;
    DWORD written;
    std::string clearStr;
    clearStr.reserve(clearWidth + displayContent.size());
    clearStr.append(clearWidth, ' ');
    SetConsoleCursorPosition(hConsole, position);
    WriteConsoleA(hConsole, clearStr.c_str(), clearStr.size(), &written, NULL);
    SetConsoleCursorPosition(hConsole, position);
    Message(Text::of(displayContent)).printContent();
}
void SelectMenu::updateMenu() {
    Message titleMessage(this->title.getContent());
    titleMessage.printContent();

    for (int i = 0; i < optionList.size(); i++) {
        Option option = optionList[i];
        std::string displayContent;
        std::string optionText = option.getContent().getContent();

        if (i == pointer) {
            displayContent = "$" + pointerColorCode + ">" + "$" + option.getColorCode() + optionText;
        } else {
            displayContent = " " + optionText;
        }

        Message optionMessage(getSpaces(optionIndentSpaces) + displayContent);
        optionMessage.printContent();
    }
}

void SelectMenu::hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SelectMenu::showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SelectMenu::onSelection() { optionList[pointer].executeSelectedFunction(); }

// 退出系统
void SelectMenu::exitSystem() { exit(0); }
