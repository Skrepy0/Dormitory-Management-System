//
// Created by Skrepy on 2026/1/2.
//

#include "../../../header/screen/login/LoginSelectMenu.h"

#include "../../../header/screen/Login/AdministratorLoginInputMenu.h"
#include "../../../header/screen/Login/UserLogInInputMenu.h"
#include "../../../header/screen/operation/AdministratorOperationMenu.h"
#include "../../../header/screen/operation/UserOperationMenu.h"
#include "../../../header/screen/operation/operations/SelectLanguage.h"
#include "../../../header/screen/registry/UserRegisterInputMenu.h"

void LoginSelectMenu::jumpSelectLanguageMenu() {
    system("cls");
    SelectLanguage selectLanguage;
    selectLanguage.loop();
    hideCursor();
}

void LoginSelectMenu::jumpUserRegisterInput() {
    system("cls");
    showCursor();
    UserRegisterInputMenu::showUserRegisterUI();
    hideCursor();
}

void LoginSelectMenu::jumpAdminOperationMenu() {
    system("cls");
    AdministratorOperationMenu menu;
    menu.loop();
    hideCursor();
}

void LoginSelectMenu::jumpUserLogInInput() {
    system("cls");
    showCursor();
    UserLoginInputMenu menu;
    menu.showUserLogin();
    hideCursor();
}

void LoginSelectMenu::jumpAdminLogInInput() {
    system("cls");
    showCursor();
    AdministratorLoginInputMenu menu;
    menu.showAdministratorLoginUI();
    hideCursor();
}


LoginSelectMenu::LoginSelectMenu() :
    SelectMenu(Text("login.title"),
               {
                       Option(Text("login.option.user"), "a", jumpUserLogInInput),
                       Option(Text("login.option.registry"), "p", jumpUserRegisterInput),
                       Option(Text("login.option.administrator"), "p", jumpAdminOperationMenu),
                       Option(Text("login.option.set_language"), "A", jumpSelectLanguageMenu),
               },
               "y", 10) {}

void LoginSelectMenu::loop() { SelectMenu::mainLoop(); }
