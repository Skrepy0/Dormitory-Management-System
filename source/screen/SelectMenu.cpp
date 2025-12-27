#include<iostream>
#include <utility>
#include"../../header/screen/SelectMenu.h"
#include <conio.h>
#include <windows.h>
#include "../../header/data/info/Message.h"

std::string SelectMenu::getSpaces(int count) {
    std::string res;
    while (count--)res+=" ";
    return res;
}

void SelectMenu::monitorKeyEvent() {
    int key = _getch();
    switch (key)
    {
        case 72: // 上箭头
            updatePointer(-1);
            break;
        case 80: // 下箭头
            updatePointer(1);
            break;
        case 13: // 回车键
            onSelection();
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
    }
    else if (index >= optionList.size()) {
        pointer = 0;
    }
    else {
        pointer = index;
    }
}

std::vector<Option> SelectMenu::getOptionList() {
    return this->optionList;
}

Text SelectMenu::getTitle() {
    return this->title;
}

void SelectMenu::setTitle(Text &title) {
    this->title = std::move(title);
}

void SelectMenu::setOptionList(std::vector<Option> &optionList) {
    this->optionList = std::move(optionList);
    // 更新optionStatusList
    if (!optionList.empty()) {
        for (auto option: optionList) {
            optionStatusList.push_back(std::make_pair(option, false));
        }
        optionStatusList[0].second = true;
    }
}

SelectMenu::SelectMenu(const Text& title, std::vector<Option> optionList,std::string pointerColorCode,int optionIndentSpaces) : title(title), optionList(std::move(optionList)),optionIndentSpaces(optionIndentSpaces),pointerColorCode(std::move(pointerColorCode)) {
    SelectMenu::init();
}

void SelectMenu::init() {
    this->isRunning = true;
    this->pointer = 0;
    this->lastPointer = 0;

    // 初始化optionStatusList
    if (!optionList.empty()) {
        for (auto & i : optionList) {
            Text text = Text::of(getSpaces(1)+i.getContent().getContent());
            Option option(text,i.getColorCode(),i.getSelectedFunction());
            optionStatusList.emplace_back(option, false);
        }
        optionStatusList[0].second = true;
    }
}

void SelectMenu::updateOptions() {
    if (pointer != lastPointer) {
        optionStatusList[pointer].second = true;
        optionStatusList[lastPointer].second = false;
    }
    for (int i = 0;i<(int)optionStatusList.size();i++) {
        if (optionStatusList[i].second) {// 如果被选中，将第一个空格替换成>
            std::string newContent = optionList[i].getContent().getContent();
            std::string front = "$"+pointerColorCode+">$"+optionList[i].getColorCode();
            front.append(newContent);
            optionStatusList[i].first.setContent(front);
        }
    }
    if (pointer != lastPointer) {
        // 将上一个选择的选项恢复正常
        std::string newContent = optionList[lastPointer].getContent().getContent();
        newContent = getSpaces(1) + newContent;
        optionStatusList[lastPointer].first.setContent(newContent);
        lastPointer = pointer;
    }
}

void SelectMenu::mainLoop() {
    hideCursor();
    while (isRunning) {
        SelectMenu::updateMenu();
        SelectMenu::monitorKeyEvent();
        system("cls");
    }
    showCursor();
}


void SelectMenu::updateMenu() {
    // 绘制标题
    Message titleMessage(this->title.getContent());
    titleMessage.printContent();
    // 更新选项
    updateOptions();
    for (auto option: optionStatusList) {
        Message optionMessage(getSpaces(optionIndentSpaces)+option.first.getContent().getContent());
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
void SelectMenu::onSelection() {// 选中后运行的函数
    void (*func)();
    func = optionList[pointer].getSelectedFunction();
    func();
}