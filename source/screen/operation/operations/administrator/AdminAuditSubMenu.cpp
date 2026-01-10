//
// Created by Skrepy on 2026/1/2.
//
#include "../../../../../header/screen/operation/operations/administrator/AdminAuditSubMenu.h"

#include "../../../../../header/screen/operation/operations/administrator/AdminAccommodationReview.h"
#include "../../../../../header/screen/operation/operations/administrator/AdminMaintenanceReview.h"

void AdminAuditSubMenu::jumpToAdminAudit() {
    system("cls");
    showCursor();
    AdminAccommodationReview menu;
    menu.inputReviewApplications();
    hideCursor();
}

void AdminAuditSubMenu::jumpMaintenanceAudit() {
    system("cls");
    showCursor();
    AdminMaintenanceReview::show();
    hideCursor();
}

AdminAuditSubMenu::AdminAuditSubMenu() :
    SelectMenu(Text("operation.administrator.audit.title"),
               {
                       Option(Text("operation.administrator.audit.option.stay_log_application"), "y", jumpToAdminAudit),
                       Option(Text("operation.administrator.audit.option.maintenance"), "d",jumpMaintenanceAudit),
               },
               "w") {}

void AdminAuditSubMenu::loop() { SelectMenu::mainLoop(); }
