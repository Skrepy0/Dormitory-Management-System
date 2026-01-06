#pragma once
#include "../../../header/screen/Login/LoginInputMenu.h"
#include <string>

// 管理员登录类（继承通用登录父类LoginInputMenu）
class AdministratorLoginInputMenu : public LoginInputMenu {
public:
    // 新增：直接生成管理员登录界面的函数
    void showAdministratorLoginUI();

protected:
    // 重写父类纯虚函数：实现管理员账号密码验证（读取AdministratorData.json）
    bool verifyCredentials(const std::string& adminId, const std::string& password) override;
};