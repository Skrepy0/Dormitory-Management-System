//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include "../../../../data/DataHelper.h"
#include "../../../SelectMenu.h"

class DormitoryInfoScreen {
private:
    std::string floor;
    std::string room_number;
    std::string building_name;
    std::string building_number;
    int total_bed;
    int vacant_bed;
    // int maintenances;
    static void show() {
        system("cls");
        SelectMenu::hideCursor();
    }

public:
    DormitoryInfoScreen() {
        nlohmann::json dormitory = DataHelper::getDormitory(DataHelper::getUser("123"));
        floor = dormitory["floor"];
        building_name = dormitory["building_name"];
        building_number = dormitory["building_number"];
        total_bed = dormitory["bed_number"];
        room_number = dormitory["room_number"];
        vacant_bed = dormitory["vacant_bed"];
        // maintenances = static_cast<int>(dormitory["maintenances"].size());
        show();
        system("pause>nul");
    }
};
