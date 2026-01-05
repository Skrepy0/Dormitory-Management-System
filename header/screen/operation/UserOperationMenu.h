#pragma once
#include "../SelectMenu.h"

class UserOperationMenu : SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpMaintenanceMenu();
    void static changePassword();

public:
    UserOperationMenu();
    void loop();
};
