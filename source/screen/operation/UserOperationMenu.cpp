#include "../../../header/screen/operation/UserOperationMenu.h"

UserOperationMenu::UserOperationMenu() :SelectMenu(Text("operation.user.title"),{
        Option(Text("operation.user.change_password"),"a"),
        Option(Text("operation.user.apply_for_repairs"),"d"),
        Option(Text("operation.user.dormitory_info"),"p"),
        Option(Text("operation.user.application"),"y")
    },"a",7){
}

void UserOperationMenu::loop() {
    SelectMenu::mainLoop();
}
