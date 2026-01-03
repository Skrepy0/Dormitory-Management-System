//
// Created by Skrepy on 2026/1/2.
//

#include "../../../header/screen/login/LoginSelectMenu.h"

#include "../../../header/screen/operation/AdministratorOperationMenu.h"

void LoginSelectMenu::jumpAdminOperationMenu() {
    system("cls");
    AdministratorOperationMenu menu;
    menu.loop();
    hideCursor();
}

LoginSelectMenu::LoginSelectMenu():SelectMenu(Text("login.title"),{
                                                  Option(Text("login.option.user"),"a"),
                                                  Option(Text("login.option.administrator"),"p",jumpAdminOperationMenu)
                                              },"y",10) {
}

void LoginSelectMenu::loop() {
    SelectMenu::mainLoop();
}
