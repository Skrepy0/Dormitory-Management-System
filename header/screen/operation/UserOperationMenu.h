#pragma once
#include "../SelectMenu.h"

class UserOperationMenu : SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpMaintenanceMenu();
    void static changePassword();
    void static jumpDormitoryInfoScreen();
    void static jumpInputCheckInApplication();
    void static jumpInputCheckOutApplication();

public:
    UserOperationMenu();
    void loop();
};
