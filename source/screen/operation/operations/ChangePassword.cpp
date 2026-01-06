#include "../../../../header/screen/operation/operations/ChangePassword.h"
#include "../../../../header/data/info/Message.h"
#include "../../../../header/data/info/Text.h"
#include "../../../../header/screen/operation/operations/Logout.h"

std::string ChangePassword::getCurrentPassword(const std::string &input) {
    Text t(input);
    currentPassword = t.getContent();
    return currentPassword;
}

std::string ChangePassword::changePassword() {
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
            pause();
            return currentPassword;
        }
    }
    std::string newPassword;
    std::string confirmPwd;
    while (true) {
        if (Logout::checkEscKey()) {
            clearScreen();
            return currentPassword;
        }

        while (true) {
            if (Logout::checkEscKey()) {
                clearScreen();
                return currentPassword;
            }

            newPassword = getNonEmptyInput("screen.operation.operations.UserChangePassword.new_password.Input");
            if (!newPassword.empty()) {
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

        if (newPassword == confirmPwd) {
            bool isConfirm = confirmOperation(
                    "screen.operation.operations.UserChangePassword.new_password.confirmation");
            if (isConfirm) {

                showSuccess("screen.operation.operations.UserChangePassword.new_password.success");
                pause();
                return newPassword;
            } else {
                showError("screen.operation.operations.UserChangePassword.new_password.confirmation.fail");
                std::cout << std::endl;
            }
        } else {
            showError("screen.operation.operations.UserChangePassword.new_password.difference");
        }
    }
}
