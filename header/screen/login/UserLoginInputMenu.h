#pragma once
#include "../../../header/screen/Login/LoginInputMenu.h"
#include <string>

class UserLoginInputMenu : public LoginInputMenu
{
public:
    void showUserLogin();
protected:
    bool verifyCredentials(const std::string& studentId, const std::string& password) override;
};