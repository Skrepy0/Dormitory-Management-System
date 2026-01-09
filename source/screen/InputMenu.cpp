#include "../../header/screen/InputMenu.h"

#include <conio.h>

#include <cctype>
#include <iostream>
#include <string>
#include <windows.h>

#include "../../header/data/info/Message.h"
#include "../../header/data/info/Text.h"

bool isAllDigit(const std::string &str) {
    for (char c: str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty(); // 空字符串也返回false
}

void InputMenu::clearInputBuffer() {
    std::cin.clear(); // 清除cin错误状态
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 清空缓冲区所有字符
}

void InputMenu::clearScreen() { system("cls"); }

void InputMenu::showTitle(const std::string &title) {
    clearScreen();
    Text t("screen.InputMenu.showTitle");
    Message message(t.getContent());
    message.printContent();
    Text t2(title);
    Message message1(t2.getContent());
    message1.printContent();
    Message message2(t.getContent());
    message2.printContent();
    std::cout << std::endl;
    Text t1("screen.InputMenu.showTitle.end");
    Message message3(t1.getContent());
    message3.printContent();
}

void InputMenu::showSuccess(const std::string &mes) {
    Text t("screen.InputMenu.showSuccess");
    Message message(t.getContent());
    message.printContent();
    Text t2(mes);
    Message message1(t2.getContent());
    message1.printContent();
}

void InputMenu::showError(const std::string &mes) {
    Text t("screen.InputMenu.showError");
    Message message(t.getContent());
    message.printContent();
    Text t2(mes);
    Message message1(t2.getContent());
    message1.printContent();
}

void InputMenu::showPrompt(const std::string &prompt) {
    Text t(prompt);
    Message message(t.getContent());
    message.printContent();
}

void InputMenu::showContent(const std::string &content) {
    Text t(content);
    Message message(t.getContent());
    message.printContent();
}

void InputMenu::pause() {
    Text t("screen.InputMenu.pause");
    Message message(t.getContent());
    message.printContent();
    clearInputBuffer();
}


std::string InputMenu::getNonEmptyInput(const std::string &prompt) {
    SetConsoleCP(CP_UTF8);
    std::string input;
    while (true) {
        showPrompt(prompt);
        getline(std::cin, input);
        if (!input.empty()) {
            return input;
        }
        Text t("screen.InputMenu.getNonEmptyInput");
        Message message(t.getContent());
        message.printContent();
    }
}

bool InputMenu::isAllDigit(const std::string &str) {
    for (char c: str) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return !str.empty();
}

std::string InputMenu::getDigitInput(const std::string &prompt, int minLen, int maxLen) {
    SetConsoleCP(CP_UTF8);
    std::string input;
    while (true) {
        input = getNonEmptyInput(prompt);
        // 校验是否为纯数字
        if (!isAllDigit(input)) {
            Text t("screen.InputMenu.getDigitInput.!isAllDigit");
            showError(t.getContent());
            continue;
        }
        // 校验长度（0表示不限制长度）
        bool lenValid = true;
        if (minLen > 0 && input.length() < minLen)
            lenValid = false;
        if (maxLen > 0 && input.length() > maxLen)
            lenValid = false;
        if (!lenValid) {
            Text t1("screen.InputMenu.getDigitInput.lenValid.left");
            Text t2("screen.InputMenu.getDigitInput.lenValid.right");
            showError(t1.getContent() + std::to_string(minLen) + "-" + std::to_string(maxLen) + t2.getContent());
            continue;
        }
        return input;
    }
}


bool InputMenu::confirmOperation(const std::string &prompt) {
    showPrompt(prompt);
    Message message(Text::of("$a(Y/N)：$r"));
    message.printContent();
    char choice;
    while (true) {
        std::cin >> choice;
        clearInputBuffer();
        if (choice == 'Y' || choice == 'y') {
            return true;
        }
        if (choice == 'N' || choice == 'n') {
            return false;
        }
        Text t("screen.InputMenu.confirmOperation.error");
        Message message2(t.getContent());
        message2.printContent();
        showContent(prompt);
        Text t1("screen.InputMenu.confirmOperation.choice");
        Message message1(t1.getContent());

        message1.printContent();
    }
}
