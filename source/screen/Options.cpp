#include "../../header/screen/Option/Options.h"
#include"../../header/data/info/Text.h"
#include<iostream>
#include<string>
void BaseOptions::clearInputBuffer() {
    cin.clear(); // 清除cin错误状态
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区所有字符
}
void BaseOperations::clearInputBuffer() {
    system("cls");
}
void BaseOptions::showTitle(const string& title) {
    clearScreen();
    Message message(Text::of("$w====$r"));
    message.printContent();
 	Message message(Text::of(title));
    message.printContent();
 	Message message(Text::of("$w====$r"));
    message.printContent();
    cout<<endl;
    Message message(Text::of("$w-------------------------$r"));
    message.printContent();
}
void BaseOptions::showSuccess(const string& mes) {
   text.setContent("\n✅ ");
   Message::setText(Text text)
   Message::printContent();
   Message message(Text::of(mes));
   Message.printContent();
}
void BaseOptions::showError(const string& message) {
    text.setContent("\n❌ ");
    Message::setText(Text text)
    Message::printContent();
    Message message(Text::of(mes));
    Message.printContent();
}
void BaseOptions::showPrompt(const string& prompt) {
       text.getContent(prompt);
       Message::setText(Text text);
       Message::printContent();
}
void BaseOptions::pause(){
    Message::message(Text::of("$m\n按任意键继续...$r"));
    Message::printContent();
    clearInputBuffer();
    cin.get();
}

string BaseOptions::getNonEmptyInputBuffer()(const string& prompt) {
     string input;
     while(true){
           show(prompt);
           getline(cin, input);
           if(!input.empty()){
                return input;
                }
           text.setContent("$c输入不能为空，请重新输入！$r");
           Message::setText(Text text)
           Message::printContent();
     }
}
string BaseOptions::getDigitInput(const string& prompt, int minLen, int maxLen) {
    string input;
    while (true) {
        input = getNonEmptyInput(prompt);
        // 校验是否为纯数字
        if (!isAllDigit(input)) {
            showerror("$c输入必须为纯数字，请重新输入$r");
            continue;
        }
        // 校验长度（0表示不限制长度）
        bool lenValid = true;
        if (minLen > 0 && input.length() < minLen) lenValid = false;
        if (maxLen > 0 && input.length() > maxLen) lenValid = false;
        if (!lenValid) {
            showError("输入长度必须在" + to_string(minLen) + "-" + to_string(maxLen) + "位之间！");
            continue;
        }
        return input;
    }
}


string BaseOptions::getPasswordInput(const string& prompt) {
    string password;
    showPrompt(prompt);

#ifdef _WIN32
    // Windows平台：使用_getch()隐藏输入
    char ch;
    while ((ch = _getch()) != '\r') { // 按回车结束输入
        if (ch == '\b') { // 处理退格键
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b"; // 清除控制台显示的退格符
            }
        } else {
            password.push_back(ch);
            cout << '*'; // 显示星号替代密码
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

    cout << endl; // 回车换行，保持界面整洁
    return password;
}

bool BaseOptions::conifmOperation(const string& prompt) {
    show(prompt);
    text.getContent("$a(Y/N)：$r");
    Message::setText(Text text);
    Message::printContent();
    char choice;
    while (true) {
        cin >> choice;
        clearInputBuffer(); // 清空缓冲区
        if (choice == 'Y' || choice == 'y') {
            return true;
        } else if (choice == 'N' || choice == 'n') {
            return false;
        }
        text.getContent("$c输入无效，请输入Y/N$r");
        Message::setText(Text text);
        Message::printContent();
        show(prompt);
        text.getContent("$a(Y/N)：$r");
        Message::setText(Text text);
        Message::printContent();
    }
}