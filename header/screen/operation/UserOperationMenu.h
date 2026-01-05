#pragma once
#include "../SelectMenu.h"

class UserOperationMenu : SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpMaintenanceMenu();

public:
    UserOperationMenu();
    void loop();
};
