//
// Created by Skrepy on 2026/1/5.
//

#include "../../../../../header/screen/operation/operations/administrator/StudentInfoManageMenu.h"

#include "../../../../../header/screen/operation/operations/administrator/AdminDormitoryManagement.h"

StudentInfoManageMenu::StudentInfoManageMenu() :
    SelectMenu(Text("operator.administrator.studentInfoManageMenu.title"),
               {
                       Option(Text("operator.administrator.studentInfoManageMenu.option.check-in"), "H",
                              []() -> void {
                                  system("cls");
                                  showCursor();
                                  AdminDormitoryManagement::showStudentCheckInRecord();
                                  hideCursor();
                              }),
                       Option(Text("operator.administrator.studentInfoManageMenu.option.check-out"), "B",
                              []() -> void {
                                  system("cls");
                                  showCursor();
                                  AdminDormitoryManagement::showStudentCheckOutRecord();
                                  hideCursor();
                              }),
               },
               "F") {}

void StudentInfoManageMenu::loop() { mainLoop(); }
