#include "../../header/screen/Options.h"

#include <conio.h>

#include"../../header/data/info/Text.h"
#include"../../header/data/info/Message.h"
#include<iostream>
#include<string>
#include<cctype>
bool isAllDigit(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) { // 注意：isdigit需要包含<cctype>头文件
            return false;
        }
    }
    return !str.empty(); // 空字符串也返回false
}
void BaseOptions::clearInputBuffer() {
    std::cin.clear(); // 清除cin错误状态
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区所有字符
}
void BaseOptions::clearScreen() {
    system("cls");
}
void BaseOptions::showTitle(const std::string& title) {
    clearScreen();
    Message message(Text::of("$w====$r"));
    message.printContent();
    Message message1(Text::of(title));
    message1.printContent();
 	Message message2(Text::of("$w====$r"));
    message2.printContent();
    std::cout<< std::endl;
    Message message3(Text::of("$w-------------------------$r"));
    message3.printContent();
}
void BaseOptions::showSuccess(const std::string& mes) {
   Message message(Text::of("\n✅ "));
   message.printContent();
   Message message1(Text::of(mes));
   message1.printContent();
}
void BaseOptions::showError(const std::string& mes) {
    Message message(Text::of("\n❌ "));
    message.printContent();
    Message message1(Text::of(mes));
    message1.printContent();
}
void BaseOptions::showPrompt(const std::string& prompt) {
       Message message(Text::of(prompt));
       message.printContent();
   }

void BaseOptions::showContent(const std::string& content)
{

    Message message(Text::of(content));
    message.printContent();
}

void BaseOptions::pause(){
    Message message(Text::of("$m\n按任意键继续...$r"));
    message.printContent();
    clearInputBuffer();
    std::cin.get();
}



std::string BaseOptions::getNonEmptyInput(const std::string& prompt)
{
    std::string input;
    while (true)
    {
        showPrompt(prompt);
        getline(std::cin, input);
        if (!input.empty())
        {
            return input;
        }
        Message message(Text::of("$c输入不能为空，请重新输入！$r"));
        message.printContent();
    }
}
bool BaseOptions::isAllDigit(const std::string& str) {
    for (char c : str) {
        if (!isdigit(c)) { // 注意：isdigit需要包含c头文件
            return false;
        }
    }
    return !str.empty(); // 空字符串也返回false
}
std::string BaseOptions::getDigitInput(const std::string& prompt, int minLen, int maxLen) {
    std::string input;
    while (true) {
        input = getNonEmptyInput(prompt);
        // 校验是否为纯数字
        if (!isAllDigit(input)) {
            showError("$c输入必须为纯数字，请重新输入$r");
            continue;
        }
        // 校验长度（0表示不限制长度）
        bool lenValid = true;
        if (minLen > 0 && input.length() < minLen) lenValid = false;
        if (maxLen > 0 && input.length() > maxLen) lenValid = false;
        if (!lenValid) {
            showError("输入长度必须在" + std::to_string(minLen) + "-" + std::to_string(maxLen) + "位之间！");
            continue;
        }
        return input;
    }
}


std::string BaseOptions::getPasswordInput(const std::string& prompt) {
    std::string password;
    showPrompt(prompt);

#ifdef _WIN32
    // Windows平台：使用_getch()隐藏输入
    char ch;
    while ((ch = _getch()) != '\r') { // 按回车结束输入
        if (ch == '\b') { // 处理退格键
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // 清除控制台显示的退格符
            }
        } else {
            password.push_back(ch);
            std::cout << '*'; // 显示星号替代密码
        }
    }
#else
    // Linux/Mac平台：临时关闭回显（需termios.h）
    // 以下为Linux/Mac适配示例，需包含<termios.h>
    struct termios oldAttr, newAttr;
    tcgetattr(STDIN_FILENO, &oldAttr); // 获取原终端属性
    newAttr = oldAttr;
    newAttr.c_lflag &= ~ECHO; // 关闭回显
    tcsetattr(STDIN_FILENO, TCSANOW, &newAttr); // 应用新属性

    getline(cin, password); // 读取密码（无回显）
    tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr); // 恢复原终端属性
#endif

    std::cout << std::endl; // 回车换行，保持界面整洁
    return password;
}

bool BaseOptions::confirmOperation(const std::string& prompt) {
    showPrompt(prompt);
    Message message(Text::of("$a(Y/N)：$r"));
    message.printContent();
    char choice;
    while (true) {
        std::cin >> choice;
        clearInputBuffer(); // 清空缓冲区
        if (choice == 'Y' || choice == 'y') {
            return true;
        } else if (choice == 'N' || choice == 'n') {
            return false;
        }
        Message message(Text::of("$c输入无效，请输入Y/N$r"));
        message.printContent();
        showContent(prompt);
        Message message1(Text::of("$a(Y/N)：$r"));

        message1.printContent();

    }
}