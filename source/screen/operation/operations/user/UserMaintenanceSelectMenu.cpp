//
// Created by Skrepy on 2026/1/5.
//

#include "../../../../../header/screen/operation/operations/user/UserMaintenanceSelectMenu.h"

#include "../../../../../header/screen/operation/operations/user/UserMaintenance.h"

void UserMaintenanceSelectMenu::jumpAddMaintenanceMenu() {
    UserMaintenance menu;
    showCursor();
    menu.submitRepair();
    hideCursor();
}

void UserMaintenanceSelectMenu::jumpValuation() {
    UserMaintenance menu;
    showCursor();
    menu.submitValuation();
    hideCursor();
}

UserMaintenanceSelectMenu::UserMaintenanceSelectMenu() :
    SelectMenu(Text("operation.user.maintenance.title"),
               {Option(Text("operation.user.maintenance.option.maintenance"), "a", jumpAddMaintenanceMenu),
                Option(Text("operation.user.maintenance.option.maintenance_valuation"), "m", jumpValuation)},
               "A", 6) {}

void UserMaintenanceSelectMenu::loop() { mainLoop(); }
