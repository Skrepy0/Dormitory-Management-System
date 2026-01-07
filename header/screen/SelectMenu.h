#pragma once
#include <iostream>
#include <vector>
#include "Option.h"

class SelectMenu {
private:
    static std::string getSpaces(int count);

protected:
    std::vector<Option> optionList; // 选项列表
    Text title; // 标题
    int optionIndentSpaces; // 选项前空格数
    std::string pointerColorCode;
    bool isRunning;
    int pointer; // 当前>指向的选项的索引
    int lastPointer; // 上一次选择的选项的索引
    int titleLine; // 标题行数(请和json文件保持一致，不然会出现渲染bug)

    void init(); // 菜单初始化函数
    void monitorKeyEvent(); // 监视输入
    void updatePointer(int direction); // 选择器上下移动与选项颜色更新

public:
    std::vector<Option> getOptionList(); // 获取选项列表

    Text getTitle(); // 获取标题

    void setOptionList(std::vector<Option> &optionList); // 设置选项列表
    void setTitle(Text &title); // 设置标题

    SelectMenu(const Text &title, std::vector<Option> optionList, std::string pointerColorCode = "p",
               int optionIndentSpaces = 6, int titleLine = 2);

    virtual ~SelectMenu() = default;

    void mainLoop(); // 主循环
    void updateOptionLine(int index);

    void updateMenu(); // 菜单更新显示函数

    virtual void onSelection(); // 选定后

    static void exitSystem(); // 退出系统
    void static hideCursor(); // 隐藏光标
    void static showCursor(); // 显示光标
};
