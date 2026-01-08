#include "../../../header/screen/Login/AdministratorLoginInputMenu.h"
#include <fstream>
#include "../../../header/data/AdminData.h"
#include "../../../header/data/HashHelper.h"
#include "../../../header/screen/InputMenu.h"

bool AdministratorLoginInputMenu::verifyCredentials(const std::string &adminId, const std::string &password) {
    try {
        int adminIndex = AdminData::findAdminById(adminId);
        if (adminIndex == -1) {
            std::cerr << "ID不存在，登录失败" << std::endl;
            return false;
        }

        nlohmann::json allAdminData = AdminData::getAdminJsonData();


        size_t hashedInputPassword = HashHelper::getHash(password);


        const auto &adminArray = allAdminData["administrator"];

        const auto &admin = adminArray[adminIndex];
        int storedHashedPwdStr = admin["password"];

        bool isPasswordMatch = (hashedInputPassword == storedHashedPwdStr);
        return isPasswordMatch;

    } catch (const std::exception &e) {
        std::cerr << "验证失败: " << e.what() << std::endl;
        return false;
    }
}

void AdministratorLoginInputMenu::showAdministratorLoginUI() {
    clearScreen();
    showTitle("screen.login.administrator.title"); // 对应学生的标题键
    std::cout << std::endl;

    std::string adminId;
    std::string idPromptKey = "screen.login.administrator.input.id.prompt"; // 管理员ID提示键
    bool loginSuccess = this->login(adminId, idPromptKey);

    clearScreen();

    if (loginSuccess) {
        showSuccess("screen.login.administrator.success"); // 管理员登录成功键
        pause();

    } else {
        showError("screen.login.administrator.fail"); // 管理员登录失败键
        pause();
    }
}
