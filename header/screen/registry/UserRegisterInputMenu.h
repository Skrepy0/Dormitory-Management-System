#pragma once
#include "../InputMenu.h"
#include <string>

class UserRegisterInputMenu : public InputMenu {
public:

    static void showUserRegisterUI();

protected:

    static bool isIdExists(const std::string& userId) ;

    static bool saveNewUser(const std::string& userId, const std::string& password);
};