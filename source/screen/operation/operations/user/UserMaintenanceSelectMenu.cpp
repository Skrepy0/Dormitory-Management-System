//
// Created by Skrepy on 2026/1/5.
//

#include "../../../../../header/screen/operation/operations/user/UserMaintenanceSelectMenu.h"

#include "../../../../../header/screen/operation/operations/user/UserMaintenance.h"

void UserMaintenanceSelectMenu::jumpAddMaintenanceMenu() {
    UserMaintenance menu;
    showCursor();
    menu.submitRepair();
    system("pause>nul");
    hideCursor();
}

UserMaintenanceSelectMenu::UserMaintenanceSelectMenu() :
    SelectMenu(Text("operation.user.maintenance.title"),
               {Option(Text("operation.user.maintenance.option.maintenance"), "a", jumpAddMaintenanceMenu),
                Option(Text("operation.user.maintenance.option.annul_maintenance"), "c"),
                Option(Text("operation.user.maintenance.option.maintenance_records"), "y"),
                Option(Text("operation.user.maintenance.option.find_maintenance_records"), "g"),
                Option(Text("operation.user.maintenance.option.maintenance_valuation"), "m")},
               "A", 6) {}

void UserMaintenanceSelectMenu::loop() { mainLoop(); }
