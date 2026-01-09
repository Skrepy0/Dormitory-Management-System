//
// Created by Skrepy on 2026/1/5.
//
#include "../../../../../header/screen/operation/operations/administrator/DormitoryManageMenu.h"

#include "../../../../../header/data/DataHelper.h"
#include "../../../../../header/screen/operation/operations/administrator/AdminDormitoryManagement.h"

void DormitoryManageMenu::jumpInputAddBuilding() {
    system("cls");
    showCursor();
    AdminDormitoryManagement::inputAddBuilding();
    hideCursor();
}

void DormitoryManageMenu::jumpInputDeleteBuilding() {
    system("cls");
    showCursor();
    AdminDormitoryManagement::inputDeleteBuilding();
    hideCursor();
}

void DormitoryManageMenu::jumpInputAddDorm() {
    system("cls");
    showCursor();
    AdminDormitoryManagement::inputAddDormRoom();
    hideCursor();
}

void DormitoryManageMenu::jumpInputDeleteDorm() {
    system("cls");
    showCursor();
    AdminDormitoryManagement::inputDeleteDormRoom();
    hideCursor();
}

void DormitoryManageMenu::jumpUpdateBuildingInfo() {}

void DormitoryManageMenu::jumpUpdateDormInfo() {}

DormitoryManageMenu::DormitoryManageMenu() :
    SelectMenu(
            Text("operation.administrator.dormitory_manage.title"),
            {Option(Text("operation.administrator.dormitory_manage.option.find_building_info"), "B"),
             Option(Text("operation.administrator.dormitory_manage.option.add_buildings"), "F", jumpInputAddBuilding),
             Option(Text("operation.administrator.dormitory_manage.option.del_buildings"), "c",
                    jumpInputDeleteBuilding),
             Option(Text("operation.administrator.dormitory_manage.option.find_dormitory_info"), "G"),
             Option(Text("operation.administrator.dormitory_manage.option.add_dormitories"), "C", jumpInputAddDorm),
             Option(Text("operation.administrator.dormitory_manage.option.del_dormitories"), "c", jumpInputDeleteDorm),
             Option(Text("operation.administrator.dormitory_manage.option.update_dormitory_status"), "G"),
             Option(Text("operation.administrator.dormitory_manage.option.update_building_status"), "H")},
            "k", 5) {}

void DormitoryManageMenu::loop() { mainLoop(); }
