#include "../../../header/screen/registry/UserRegisterInputMenu.h"
// 假设UserData.h位于header/data目录下，根据你的项目路径修改
#include "../../../header/data/UserData.h"
#include <fstream>
#include <iostream>
#include <iomanip>


void UserRegisterInputMenu::showUserRegisterUI() {
    clearScreen();
    showTitle("screen.register.user.title"); // 配置Key：====用户注册界面====
    std::cout << std::endl;
    std::string userId = getDigitInput("screen.register.user.input.id", 12, 12);

    if (isIdExists(userId)) {
        showError("screen.register.id.exist"); // 该ID已注册
        pause();
        return;
    }


    std::string pwd = getNonEmptyInput("screen.register.input.pwd");


    std::string confirmPwd = getNonEmptyInput("screen.register.input.confirm.pwd");


    if (pwd != confirmPwd) {
        showError("screen.register.pwd.not.match"); // 两次密码不一致
        pause();
        return;
    }


    if (saveNewUser(userId, pwd)) {
        clearScreen();
        showSuccess("screen.register.success"); // 注册成功
        pause();
    } else {
        showError("screen.register.fail"); // 注册失败
        pause();
    }
}

bool UserRegisterInputMenu::isIdExists(const std::string &userId) {

    long long userIndex = UserData::findUserById(userId);
    return userIndex != -1;
}

bool UserRegisterInputMenu::saveNewUser(const std::string &userId, const std::string &password) {
    try {
        nlohmann::json newUserJson;
        newUserJson["name"] = "";
        newUserJson["id"] = userId;
        newUserJson["password"] = password;
        newUserJson["email"] = "";


        nlohmann::json dormitoryJson;
        dormitoryJson["bed_number"] = "";
        dormitoryJson["building_number"] = "";
        dormitoryJson["room_number"] = "";
        newUserJson["dormitory"] = dormitoryJson;


        UserData::addFromJson(newUserJson);
        return true;
    } catch (const std::exception &e) {
        showError("保存用户失败：" + std::string(e.what()));
        return false;
    }
}
