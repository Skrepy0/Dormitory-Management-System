//
// Created by Skrepy on 2026/1/5.
//

#include "../../../../../header/screen/operation/operations/administrator/StudentInfoManageMenu.h"

StudentInfoManageMenu::StudentInfoManageMenu() :
    SelectMenu(Text("operator.administrator.studentInfoManageMenu.title"),
               {
                       Option(Text("operator.administrator.studentInfoManageMenu.option.dormitory"), "a"),
                       Option(Text("operator.administrator.studentInfoManageMenu.option.check-in"), "H"),
                       Option(Text("operator.administrator.studentInfoManageMenu.option.check-out"), "B"),
               },
               "F") {}

void StudentInfoManageMenu::loop() { mainLoop(); }
