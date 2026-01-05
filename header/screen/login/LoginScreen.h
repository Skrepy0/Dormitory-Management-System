#pragma once
// 包含依赖的头文件（对应你的项目路径）
#include "../InputMenu.h"
#include "../../screen/operation/operations/Logout.h"
#include "../../data/info/Text.h"
#include "../../data/info/Message.h"
class LoginScreen : public InputMenu {
public:
    bool login(std::string& key,std::string&prompt);
protected:

    virtual bool verifyCredentials(const std::string& studentId, const std::string& password) = 0;
};