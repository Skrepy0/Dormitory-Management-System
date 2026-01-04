//
// Created by Skrepy on 2026/1/2.
//
#pragma once
#include "../SelectMenu.h"

class LoginSelectMenu : public SelectMenu{
private:
    static void jumpSelectLanguageMenu();

    static void jumpAdminOperationMenu();
public:
    LoginSelectMenu();
    void loop();
};
