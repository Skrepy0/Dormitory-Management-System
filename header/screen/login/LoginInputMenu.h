#pragma once
// 包含依赖的头文件（对应你的项目路径）
#include "../../data/info/Message.h"
#include "../../data/info/Text.h"
#include "../../screen/operation/operations/Logout.h"
#include "../InputMenu.h"
class LoginInputMenu : public InputMenu {
public:
    static nlohmann::json data;
    bool login(std::string &key, std::string &prompt);
    virtual ~LoginInputMenu() = default;

protected:
    virtual bool verifyCredentials(const std::string &studentId, const std::string &password) = 0;
};
