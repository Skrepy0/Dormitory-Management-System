//
// Created by Skrepy on 2026/1/2.
//
#pragma once
#include "../SelectMenu.h"

class LoginSelectMenu : public SelectMenu {
private:
    static void jumpSelectLanguageMenu();
    static void jumpUserRegisterInput();
    static void jumpAdminOperationMenu();
    static void jumpUserLogInInput();

public:
    LoginSelectMenu();
    void loop();
};
