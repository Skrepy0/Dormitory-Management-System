#include<iostream>
#include <utility>
#include"../../header/menu/Menu.h"
#include <conio.h>

#include "../../header/data/info/Message.h"

std::string Menu::getSpaces(int count) {
    std::string res;
    while (count--)res+=" ";
    return res;
}

void Menu::monitorKeyEvent() {
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

void Menu::updatePointer(int direction) {
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

std::vector<Option> Menu::getOptionList() {
    return this->optionList;
}

Text Menu::getTitle() {
    return this->title;
}

void Menu::setTitle(Text &title) {
    this->title = std::move(title);
}

void Menu::setOptionList(std::vector<Option> &optionList) {
    this->optionList = std::move(optionList);
    // 更新optionStatusList
    if (!optionList.empty()) {
        for (auto option: optionList) {
            optionStatusList.push_back(std::make_pair(option, false));
        }
        optionStatusList[0].second = true;
    }
}

Menu::Menu(Text title, std::vector<Option> optionList) : title(title), optionList(std::move(optionList)) {
    Menu::init();
}

void Menu::init() {
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

void Menu::updateOptions() {
    if (pointer != lastPointer) {
        optionStatusList[pointer].second = true;
        optionStatusList[lastPointer].second = false;
    }
    for (int i = 0;i<(int)optionStatusList.size();i++) {
        if (optionStatusList[i].second) {// 如果被选中，将第一个空格替换成>
            std::string newContent = optionList[i].getContent().getContent();
            std::string front = "$c>$"+optionList[i].getColorCode();
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

void Menu::mainLoop() {
    while (isRunning) {
        Menu::updateMenu();
        Menu::monitorKeyEvent();
        system("cls");
    }
}


void Menu::updateMenu() {
    // 绘制标题
    Message titleMessage(this->title.getContent());
    titleMessage.printContent();
    // 更新选项
    updateOptions();
    for (auto option: optionStatusList) {
        Message optionMessage(getSpaces(OPTION_INDENT_SPACES)+option.first.getContent().getContent());
        optionMessage.printContent();
    }
}

void Menu::onSelection() {// 选中后运行的函数
    void (*func)();
    func = optionList[pointer].getSelectedFunction();
    func();
}