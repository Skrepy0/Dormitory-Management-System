#include "../../../header/screen/registry/RegisterInputMenu.h"
#include <fstream>
#include <iomanip>
#include <iostream>
// 1. 删除：#include "../../Logout.h" （移除Logout头文件包含）

// 实现：验证两次密码是否一致（私有函数，封装细节）
bool RegisterInputMenu::isPasswordMatch(const std::string &pwd, const std::string &confirmPwd) {
    return pwd == confirmPwd;
}

// 实现：公共接口——显示注册界面（封装通用注册流程）
void RegisterInputMenu::showRegisterUI(const std::string &titleKey, const std::string &idPromptKey) {
    clearScreen(); // 复用InputMenu的清屏函数（继承）
    showTitle(titleKey); // 复用InputMenu的标题函数（继承）

    // 1. 输入ID（复用InputMenu的数字输入函数）
    std::string id = getDigitInput(idPromptKey, 12, 12);
    // 2. 删除：Logout::checkEscKey() 条件判断块
    // 原代码：
    // if (Logout::checkEscKey()) {
    //     clearScreen();
    //     showContent("screen.register.cancel");
    //     return;
    // }

    // 2. 检查ID唯一性（调用子类实现的纯虚函数——多态）
    if (isIdExists(id)) {
        showError("screen.register.id.exist");
        pause(); // 复用InputMenu的暂停函数
        return;
    }

    // 3. 输入密码（复用InputMenu的非空输入函数）
    std::string pwd = getInput("screen.register.input.pwd");
    // 3. 删除：Logout::checkEscKey() 条件判断块
    // 原代码：
    // if (Logout::checkEscKey()) {
    //     clearScreen();
    //     showContent("screen.register.cancel");
    //     return;
    // }

    // 4. 输入确认密码
    std::string confirmPwd = getInput("screen.register.input.confirm.pwd");
    // 4. 删除：Logout::checkEscKey() 条件判断块
    // 原代码：
    // if (Logout::checkEscKey()) {
    //     clearScreen();
    //     showContent("screen.register.cancel");
    //     return;
    // }

    // 5. 验证密码（调用封装的辅助函数）
    if (!isPasswordMatch(pwd, confirmPwd)) {
        showError("screen.register.pwd.not.match");
        pause();
        return;
    }

    // 6. 保存新用户（调用子类实现的纯虚函数——多态）
    if (saveNewUser(id, pwd)) {
        clearScreen();
        showSuccess("screen.register.success");
        pause();
    } else {
        showError("screen.register.fail");
        pause();
    }
}
