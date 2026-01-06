#pragma once
#include "../../InputMenu.h"
class ChangePassword : public InputMenu {
public:
    std::string getCurrentPassword(const std::string &input);
    std::string changePassword();
private:
    std::string currentPassword;
};
