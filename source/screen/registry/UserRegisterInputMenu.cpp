#include "../../../header/screen/registry/UserRegisterInputMenu.h"
#include <fstream>
#include <iostream>
#include "../../../header/data/UserData.h"

bool UserRegisterInputMenu::isIdExists(const std::string &userId) {
    long long userIndex = UserData::findUserById(userId);
    return userIndex != -1;
}
bool UserRegisterInputMenu::saveNewUser(const std::string &userId, const std::string &name, const std::string &email,
                                        const std::string &password) {
    try {
        UserData(name, userId, password, email, Dormitory("", "", "", "", -1, -1));

        nlohmann::json allUserData = UserData::readJson();
        UserData userInstance("", "", "", "", Dormitory("", "", "", "", 0, 0));

        userInstance.setData(allUserData);

        return userInstance.writeToFile();


    } catch (const std::exception &e) {
        std::cerr << "保存用户失败：" << e.what() << std::endl;
        return false;
    }
}

// 3. 修正：showUserRegisterUI（解决“不可到达代码”“条件始终为false”）
void UserRegisterInputMenu::showUserRegisterUI() {
    clearScreen();
    showTitle("screen.register.user.title");
    std::cout << std::endl;

    // 输入用户ID
    std::string userId = getDigitInput("screen.register.user.input.id", 12, 12);
    if (isIdExists(userId)) { // 此处条件不会“始终为false”（ID可能存在）
        showError("screen.register.id.exist");
        pause();
        return; // return后不会执行后续代码，消除“不可到达”
    }

    // 输入姓名
    std::string name = getInput("screen.register.user.input.name");
    // 输入邮箱
    std::string email = getInput("screen.register.user.input.email");
    // 输入密码
    std::string pwd = getInput("screen.register.input.pwd");
    std::string confirmPwd = getInput("screen.register.input.confirm.pwd");
    if (pwd != confirmPwd) {
        showError("screen.register.pwd.not.match");
        pause();
        return; // return后不会执行后续代码，消除“不可到达”
    }

    // 保存新用户（修正参数传递：直接传pwd，不是“password:pwd”）
    clearScreen();
    if (saveNewUser(userId, name, email, pwd)) {
        showSuccess("screen.register.success");
    } else {
        showError("screen.register.fail");
    }
    pause();
}
