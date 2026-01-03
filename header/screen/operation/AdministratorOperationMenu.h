#pragma once
#include "../SelectMenu.h"

class AdministratorOperationMenu :public SelectMenu{
private:
    void static jumpSelectLanguageMenu();
    void static jumpAuditMenu();
public:
    AdministratorOperationMenu();
    void loop();
};


