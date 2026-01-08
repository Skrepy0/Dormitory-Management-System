#include "../../../header/screen/Login/UserLogInInputMenu.h"
#include <direct.h>
#include <fstream>
#include <iostream>
#include "../../../header/data/UserData.h"

bool UserLoginInputMenu::verifyCredentials(const std::string &studentId, const std::string &password) {
    try {
        long long userIndex = UserData::findUserById(studentId);
        if (userIndex == -1) {
            return false;
        }


        nlohmann::json allUserData = UserData::readJson();


        const auto &user = allUserData["user"][userIndex];


        return user["password"] == password;

    } catch (const std::exception &e) {

        std::cerr << "登录验证失败：" << e.what() << std::endl;
        return false;
    }
}

void UserLoginInputMenu::showUserLogin() {
    clearScreen();
    showTitle("screen.login.student.title");
    std::cout << std::endl;
    std::string studentId;
    std::string idPromptKey = "screen.login.student.input.id.prompt";
    bool loginSuccess = this->login(studentId, idPromptKey);

    clearScreen();
    if (loginSuccess) {
        showSuccess("screen.login.student.success");
        pause();
    } else {
        showError("screen.login.student.fail");
        pause();
        bool backToSelect = confirmOperation("screen.login.student.back.select");
        if (backToSelect) {
            return;
        } else {
            this->showUserLogin();
        }
    }
}
