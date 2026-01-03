#include "../../../header/screen/operation/UserOperationMenu.h"

#include "../../../header/screen/operation/operations/SelectLanguage.h"
void UserOperationMenu::jumpSelectLanguageMenu(){
    system("cls");
    SelectLanguage selectLanguage;
    selectLanguage.loop();
    hideCursor();
}
UserOperationMenu::UserOperationMenu() :SelectMenu(Text("operation.user.title"),{
      Option(Text("operation.user.option.change_password"),"a"),
      Option(Text("operation.user.option.apply_for_repairs"),"d"),
      Option(Text("operation.user.option.dormitory_info"),"p"),
      Option(Text("operation.user.option.application"),"y"),
      Option(Text("operation.user.option.language"),"g",jumpSelectLanguageMenu),
      Option(Text("operation.user.option.exit"),"p"),
},"a",7){
}

void UserOperationMenu::loop() {
    SelectMenu::mainLoop();
}