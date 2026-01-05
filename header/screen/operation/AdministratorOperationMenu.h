#pragma once
#include "../SelectMenu.h"

class AdministratorOperationMenu : public SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpAuditMenu();
    void static jumpDormitoryManageMenu();

public:
    AdministratorOperationMenu();
    void loop();
};
