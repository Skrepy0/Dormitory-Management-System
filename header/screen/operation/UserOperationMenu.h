#pragma once
#include "../SelectMenu.h"

class UserOperationMenu : SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpMaintenanceMenu();
    void static changePassword();
    void static jumpDormitoryInfoScreen();

public:
    UserOperationMenu();
    void loop();
};
