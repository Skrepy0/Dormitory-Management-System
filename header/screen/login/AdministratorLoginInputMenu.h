#pragma once
#include "../../../header/screen/Login/LoginInputMenu.h"
#include <string>

class AdministratorLoginInputMenu final : public LoginInputMenu {
public:
    void showAdministratorLoginUI();

protected:
    bool verifyCredentials(const std::string& adminId, const std::string& password) override;
};