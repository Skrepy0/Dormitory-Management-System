#include "../../../header/screen/operation/AdministratorOperationMenu.h"

#include "../../../header/screen/operation/operations/SelectLanguage.h"
#include "../../../header/screen/operation/operations/administrator/AdminAuditSubMenu.h"

void AdministratorOperationMenu::jumpSelectLanguageMenu(){
    system("cls");
    SelectLanguage selectLanguage;
    selectLanguage.loop();
    hideCursor();
}

void AdministratorOperationMenu::jumpAuditMenu() {
    system("cls");
    AdminAuditSubMenu menu;
    menu.loop();
    hideCursor();
}

AdministratorOperationMenu::AdministratorOperationMenu():SelectMenu(Text("operation.administrator.title"),{
    Option(Text("operation.administrator.option.dormitory_management"),"a"),
    Option(Text("operation.administrator.option.verify"),"y",jumpAuditMenu),
    Option(Text("operation.administrator.option.student_info"),"p"),
    Option(Text("operation.administrator.option.change_password"),"g"),
    Option(Text("operation.administrator.option.language"),"d",jumpSelectLanguageMenu),
    Option(Text("operation.administrator.option.exit"),"c",exitSystem)
                                                                    },"d",8) {
}

void AdministratorOperationMenu::loop() {
    SelectMenu::mainLoop();
}
