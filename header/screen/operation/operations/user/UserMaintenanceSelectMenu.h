//
// Created by Skrepy on 2026/1/5.
//
#pragma once
#include "../../../SelectMenu.h"

class UserMaintenanceSelectMenu : public SelectMenu {
private:
    static void jumpAddMaintenanceMenu();

public:
    UserMaintenanceSelectMenu();
    void loop();
};
