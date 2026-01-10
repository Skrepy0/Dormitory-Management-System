//
// Created by Skrepy on 2026/1/2.
//
#pragma once
#include "../../../SelectMenu.h"

class AdminAuditSubMenu : public SelectMenu {
private:
    static void jumpToAdminAudit();
    static void jumpMaintenanceAudit();
public:
    AdminAuditSubMenu();
    void loop();
};
