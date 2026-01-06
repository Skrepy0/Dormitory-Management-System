#include "../../../header/screen/Login/UserLogInInputMenu.h"
#include <fstream>

bool UserLoginInputMenu::verifyCredentials(const std::string& studentId, const std::string& password) {
    std::ifstream file("../../../data/data/UserData.json");
    nlohmann::json jsonData;
    file >> jsonData;

    for (const auto& user : jsonData["user"]) {
        std::cout << "读取到的id：" << user["id"] << "，类型：" << user["id"].type_name() << std::endl;
        std::cout << "读取到的password：" << user["password"] << "，类型：" << user["password"].type_name() << std::endl;
        std::cout << "输入的password：" << password << "，类型：字符串" << std::endl;

        if (user["id"] == studentId && user["password"] == password) {
            return true;
        }
    }
    return false;
}

void UserLoginInputMenu::showUserLogin() {
    clearScreen();
    showTitle("screen.login.student.title"); // 读取配置Key显示标题

    std::string studentId;
    std::string idPromptKey = "screen.login.student.input.id.prompt";

    bool loginSuccess = this->login(studentId, idPromptKey);

    clearScreen();
    if (loginSuccess) {
        showSuccess("screen.login.student.success" );
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
