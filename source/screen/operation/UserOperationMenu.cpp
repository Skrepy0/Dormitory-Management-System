#include "../../../header/screen/operation/UserOperationMenu.h"

#include "../../../header/screen/operation/operations/SelectLanguage.h"
#include "../../../header/screen/operation/operations/user/UserMaintenanceSelectMenu.h"

void UserOperationMenu::jumpSelectLanguageMenu() {
    system("cls");
    SelectLanguage selectLanguage;
    selectLanguage.loop();
    hideCursor();
}

void UserOperationMenu::jumpMaintenanceMenu() {
    system("cls");
    UserMaintenanceSelectMenu menu;
    menu.loop();
    hideCursor();
}

UserOperationMenu::UserOperationMenu() :
    SelectMenu(Text("operation.user.title"),
               {
                       Option(Text("operation.user.option.change_password"), "a"),
                       Option(Text("operation.user.option.apply_for_repairs"), "d", jumpMaintenanceMenu),
                       Option(Text("operation.user.option.dormitory_info"), "p"),
                       Option(Text("operation.user.option.application"), "y"),
                       Option(Text("operation.user.option.language"), "g", jumpSelectLanguageMenu),
                       Option(Text("operation.user.option.exit"), "p", exitSystem),
               },
               "a", 7) {}

void UserOperationMenu::loop() { SelectMenu::mainLoop(); }
