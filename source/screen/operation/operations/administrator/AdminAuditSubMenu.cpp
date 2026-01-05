//
// Created by Skrepy on 2026/1/2.
//
#include "../../../../../header/screen/operation/operations/administrator/AdminAuditSubMenu.h"

AdminAuditSubMenu::AdminAuditSubMenu() :
    SelectMenu(Text("operation.administrator.audit.title"),
               {
                       Option(Text("operation.administrator.audit.option.check_in_application"), "a"),
                       Option(Text("operation.administrator.audit.option.check_out_application"), "y"),
                       Option(Text("operation.administrator.audit.option.maintenance"), "d"),
               },
               "w") {}

void AdminAuditSubMenu::loop() { SelectMenu::mainLoop(); }
