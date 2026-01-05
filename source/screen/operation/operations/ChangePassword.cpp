#include "../../../../header/screen/operation/operations/ChangePassword.h"
#include "../../../../header/data/info/Message.h"
#include "../../../../header/data/info/Text.h"
#include "../../../../header/screen/operation/operations/Logout.h"

std::string ChangePassword::changePassword(const std::string &password) {
    std::string currentPassword;
    Text t(password);
    currentPassword = t.getContent();

    if (Logout::checkEscKey()) {
        clearScreen();
        return currentPassword;
    }
    std::string oldPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.original_password.Input.");
    bool change = false;
    int count = 1;


    while (!change) {
        if (Logout::checkEscKey()) {
            clearScreen();
            return currentPassword;
        }


        if (oldPwd != currentPassword) {
            showError("screen.operation.operations.UserChangePassword.original_password.Input.error");
            if (Logout::checkEscKey()) {
                clearScreen();
                return currentPassword;
            }

            oldPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.Password.Input.again");
            count++;
        } else {
            change = true;
        }
        if (count > 5) {
            showError("screen.operation.operations.UserChangePassword.Password.Input.again.error");
            // clearScreen(); // 失败后也清空界面
            return currentPassword;
        }
    }
    std::string newPwd;
    std::string confirmPwd;
    // 外层循环：直到两次密码输入一致
    while (true) {
        // 检查ESC（保留原逻辑）
        if (Logout::checkEscKey()) {
            clearScreen();
            return currentPassword;
        }

        while (true) {
            if (Logout::checkEscKey()) {
                clearScreen();
                return currentPassword;
            }

            newPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.new_password.Input");
            if (!newPwd.empty()) {
                break;
            }

            showError("screen.operation.operations.UserChangePassword.new_password.empty");
            std::cout << std::endl;

            if (Logout::checkEscKey()) {
                clearScreen();
                return currentPassword;
            }
        }


        if (Logout::checkEscKey()) {
            clearScreen();
            return currentPassword;
        }


        confirmPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.new_password.Input.again");


        if (Logout::checkEscKey()) {
            clearScreen();
            return currentPassword;
        }

        if (newPwd == confirmPwd) {
            break;
        } else {
            showError("screen.operation.operations.UserChangePassword.new_password.difference");
        }
    }
}
