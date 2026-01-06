//
// Created by Skrepy on 2026/1/5.
//
#include "../../../../../header/screen/operation/operations/administrator/DormitoryManageMenu.h"

DormitoryManageMenu::DormitoryManageMenu() :
    SelectMenu(Text("operation.administrator.dormitory_manage.title"),
               {Option(Text("operation.administrator.dormitory_manage.option.find_building_info"), "B"),
                Option(Text("operation.administrator.dormitory_manage.option.add_buildings"), "F"),
                Option(Text("operation.administrator.dormitory_manage.option.del_buildings"), "c"),
                Option(Text("operation.administrator.dormitory_manage.option.find_dormitory_info"), "G"),
                Option(Text("operation.administrator.dormitory_manage.option.add_dormitories"), "C"),
                Option(Text("operation.administrator.dormitory_manage.option.del_dormitories"), "c"),
                Option(Text("operation.administrator.dormitory_manage.option.update_dormitory_status"), "H")},
               "k", 5) {}

void DormitoryManageMenu::loop() { mainLoop(); }
