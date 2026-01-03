#pragma once
#include "../SelectMenu.h"

class UserOperationMenu:SelectMenu {
private:
    void static jumpSelectLanguageMenu();
public:
    UserOperationMenu();
    void loop();
};
