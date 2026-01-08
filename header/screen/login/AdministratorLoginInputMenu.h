#pragma once
#include <string>
#include "../../../header/screen/Login/LoginInputMenu.h"

class AdministratorLoginInputMenu final : public LoginInputMenu {
public:
    void showAdministratorLoginUI();

protected:
    bool verifyCredentials(const std::string &adminId, const std::string &password) override;
};
