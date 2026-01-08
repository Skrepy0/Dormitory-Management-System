#pragma once
#include <string>
#include "../InputMenu.h"
using json = nlohmann::json;
class UserRegisterInputMenu : public InputMenu {
public:
    static void showUserRegisterUI();

protected:
    static bool isIdExists(const std::string &userId);

    static bool saveNewUser(const std::string &userId, const std::string &name, const std::string &email,
                            const std::string &password);
};
