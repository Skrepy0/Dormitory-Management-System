#pragma once
#include <iostream>
#include <limits>
#include "../../header/data/info/Text.h"
#include "../../header/screen/Option.h"
class InputMenu {
private:
    Text text;

public: // 输出类：
    static void showTitle(const std::string &title); // 显示菜单标题
    static void clearInputBuffer(); // 辅助函数，用于清空cin可能带来的负面效果
    static void clearScreen(); // 用于清空屏幕
    static void showSuccess(const std::string &message); // 显示成功提示
    static void showError(const std::string &message); // 显示错误提示
    static void showPrompt(const std::string &message); // 显示普通提示文本
    static void showContent(const std::string &content);
    static void pause(); // 暂停等待（按任意键继续）
    // 输入类：
    static std::string getDigitInput(const std::string &prompt, int minlen = 0,
                                     int maxlen = 0); // 获取纯数字输入（如学号）
    static std::string getNonEmptyInput(const std::string &prompt); // 获取非空字符串输入（如姓名，学号）
    static bool isAllDigit(const std::string &str);

    static bool confirmOperation(const std::string &prompt); // 确认操作
};
// 目前我只把自己能想到的写上去了，以后要是有用的再加
// 这个其中最常用的是 void showPrompt(const string& message);
/*例如Options::showPrompt("请输入您的密码")，这个会按我们定义的text和messaged的形式输出，其他使用都大同小异
主要是用这个函数，其他可能偶尔用一下，用法和这个函数一样，只是我在其中增加了一些其他输出
如showTitle(),你传进去一个字符串它会显示
====字符串====
-------------------------
如果还要调整边距，具体问题具体分析，再加上就行
然后就主要是是这个确认操作，prompt是用户要确认的操作，它会先提示用户选Y或者N,Y就是确认，N就是否认，
要是用户乱选，就会提醒他输入无效，下次让他输入，直到他确认答案
这个输入就相当于让用户输入一下，咱们检查一下，并且通过我们的处理，输出我们想要的颜色和格式*/
