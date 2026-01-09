#pragma once
#include "../SelectMenu.h"

class AdministratorOperationMenu : public SelectMenu {
private:
    void static jumpSelectLanguageMenu();
    void static jumpAuditMenu();
    void static jumpDormitoryManageMenu();
    void static changePassword();
    void static jumpStudentInfoManageMenu();

public:
    AdministratorOperationMenu();
    void loop();
};
