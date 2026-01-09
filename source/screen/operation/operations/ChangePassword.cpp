#include "../../../../header/screen/operation/operations/ChangePassword.h"

#include "../../../../header/data/DataHelper.h"
#include "../../../../header/data/info/Message.h"
#include "../../../../header/data/info/Text.h"
#include "../../../../header/screen/operation/operations/Logout.h"

std::string ChangePassword::getCurrentPassword(const std::string &input) {
    currentPassword = input;
    return currentPassword;
}

std::string ChangePassword::changePassword() {
    nlohmann::json data = DataHelper::readTempFromJson();
    nlohmann::json operatorData;
    std::string id = data["id"];
    if (data["type"] == "user") {
        operatorData = DataHelper::getUser(id);
        currentPassword = operatorData["password"];
    } else {
        operatorData = DataHelper::getAdmin(id);
        currentPassword = operatorData["password"];
    }

    if (Logout::checkEscKey()) {
        clearScreen();
        return currentPassword;
    }
    std::string oldPwd = HashHelper::simpleHashString(
            getNonEmptyInput("screen.operation.operations.UserChangePassword.original_password.Input."));
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
            bool isConfirm =
                    confirmOperation("screen.operation.operations.UserChangePassword.new_password.confirmation");
            if (isConfirm) {

                showSuccess("screen.operation.operations.UserChangePassword.new_password.success");
                operatorData["password"] = HashHelper::simpleHashString(newPassword);
                if (data["type"] == "user") {
                    UserData::eraseUserById(id);
                    UserData::addFromJson(operatorData);
                } else if (data["type"] == "admin") {
                    AdminData::deleteAdmin(AdminData::findAdminById(id));
                    AdminData::addAdmin(operatorData);
                }
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
