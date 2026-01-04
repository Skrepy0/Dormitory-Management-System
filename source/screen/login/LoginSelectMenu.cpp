//
// Created by Skrepy on 2026/1/2.
//

#include "../../../header/screen/login/LoginSelectMenu.h"

#include "../../../header/screen/operation/AdministratorOperationMenu.h"
#include "../../../header/screen/operation/operations/SelectLanguage.h"

void LoginSelectMenu::jumpSelectLanguageMenu(){
    system("cls");
    SelectLanguage selectLanguage;
    selectLanguage.loop();
    hideCursor();
}
void LoginSelectMenu::jumpAdminOperationMenu() {
    system("cls");
    AdministratorOperationMenu menu;
    menu.loop();
    hideCursor();
}

LoginSelectMenu::LoginSelectMenu():SelectMenu(Text("login.title"),{
                                                  Option(Text("login.option.user"),"a"),
                                                  Option(Text("login.option.administrator"),"p",jumpAdminOperationMenu),
                                                  Option(Text("login.option.set_language"),"A",jumpSelectLanguageMenu),
                                              },"y",10) {
}

void LoginSelectMenu::loop() {
    SelectMenu::mainLoop();
}
