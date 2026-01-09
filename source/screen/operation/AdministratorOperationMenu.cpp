#include "../../../header/screen/operation/AdministratorOperationMenu.h"

#include "../../../header/data/DataHelper.h"
#include "../../../header/screen/operation/operations/ChangePassword.h"
#include "../../../header/screen/operation/operations/SelectLanguage.h"
#include "../../../header/screen/operation/operations/administrator/AdminAuditSubMenu.h"
#include "../../../header/screen/operation/operations/administrator/DormitoryManageMenu.h"
#include "../../../header/screen/operation/operations/administrator/StudentInfoManageMenu.h"

void AdministratorOperationMenu::jumpSelectLanguageMenu() {
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

void AdministratorOperationMenu::jumpDormitoryManageMenu() {
    system("cls");
    DormitoryManageMenu menu;
    menu.loop();
    hideCursor();
}

void AdministratorOperationMenu::changePassword() {
    system("cls");
    showCursor();
    ChangePassword screen;
    screen.changePassword();
    hideCursor();
    system("pause>nul");
}

void AdministratorOperationMenu::jumpStudentInfoManageMenu() {
    system("cls");
    showCursor();
    StudentInfoManageMenu menu;
    menu.loop();
    hideCursor();
    system("pause>nul");
}


AdministratorOperationMenu::AdministratorOperationMenu() :
    SelectMenu(Text("operation.administrator.title"),
               {Option(Text("operation.administrator.option.dormitory_management"), "a", jumpDormitoryManageMenu),
                Option(Text("operation.administrator.option.verify"), "y", jumpAuditMenu),
                Option(Text("operation.administrator.option.student_info"), "p",jumpStudentInfoManageMenu),
                Option(Text("operation.administrator.option.change_password"), "g", changePassword),
                Option(Text("operation.administrator.option.language"), "d", jumpSelectLanguageMenu),
                Option(Text("operation.administrator.option.exit"), "c", exitSystem)},
               "d", 8) {}

void AdministratorOperationMenu::loop() { SelectMenu::mainLoop(); }
