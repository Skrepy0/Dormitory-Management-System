#include "../../../header/screen/Login/AdministratorLoginInputMenu.h"
#include <fstream>
#include "../../../header/screen/InputMenu.h"

bool AdministratorLoginInputMenu::verifyCredentials(const std::string& adminId, const std::string& password) {
    std::string filePath = "data/data/Admin.json";
    nlohmann::json jsonData;

    for (const auto& administrator : jsonData["administrator"]) {
        if (administrator["id"] == adminId && administrator["password"] == password) {
            return true; // 验证成功
        }
    }

    return false;
}

void AdministratorLoginInputMenu::showAdministratorLoginUI() {
    showTitle("screen.login.administrator.title");

    std::string adminId;
    std::string loginPrompt = "screen.login.administrator.input.id.prompt";

    bool loginSuccess = this->login(adminId, loginPrompt);

    clearScreen();
    if (loginSuccess) {
        showSuccess("screen.login.administrator.success" ); // 配置Key："登录成功！欢迎你，管理员ID："
        pause();

    } else {
        showError("screen.login.administrator.fail"); // 配置Key："登录失败！管理员ID/密码错误，或取消登录"
        pause();
    }
}
