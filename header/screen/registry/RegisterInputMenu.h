#pragma once
#include <string>
#include "../InputMenu.h"

class RegisterInputMenu : public InputMenu {
public:
    virtual ~RegisterInputMenu() = default;
    void showRegisterUI(const std::string &titleKey, const std::string &idPromptKey);

protected:
    virtual bool isIdExists(const std::string &id) = 0;
    virtual bool saveNewUser(const std::string &id, const std::string &password) = 0;

private:
    static bool isPasswordMatch(const std::string &pwd, const std::string &confirmPwd);
};
