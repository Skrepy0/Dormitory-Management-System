//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include "../../../../data/DataHelper.h"
#include "../../../../data/info/Message.h"
#include "../../../SelectMenu.h"

class DormitoryInfoScreen {
private:
    std::string user_name;
    std::string floor;
    std::string room_number;
    std::string building_name;
    std::string building_number;
    int bed_number;
    int vacant_bed;
    // int maintenances;
    void show() {
        system("cls");
        SelectMenu::hideCursor();
        Message(Text("operation.user.dormitory_info.title")).printContent();
        Message(Text("operation.user.dormitory_info.info.welcome_front")
                        .append(Text::of(user_name))
                        .append(Text("operation.user.dormitory_info.info.welcome_back")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.building_name")
                        .append(Text::of(building_name))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.building_number")
                        .append(Text::of(building_number))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.floor").append(Text::of(floor)).append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.room_number")
                        .append(Text::of(room_number))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.bed_number")
                        .append(Text::intToText(bed_number))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.vacant_bed")
                        .append(Text::intToText(vacant_bed))
                        .append(Text::of("$r\n")))
                .printContent();
    }

public:
    DormitoryInfoScreen() {
        nlohmann::json dormitory = DataHelper::getDormitory(DataHelper::getUser(DataHelper::readTempFromJson()["id"]));
        user_name = DataHelper::getUser(DataHelper::readTempFromJson()["id"])["name"];
        floor = dormitory["floor"];
        building_name = dormitory["building_name"];
        building_number = dormitory["building_number"];
        bed_number = dormitory["bed_number"];
        room_number = dormitory["room_number"];
        vacant_bed = dormitory["vacant_bed"];
        // maintenances = static_cast<int>(dormitory["maintenances"].size());
        show();
        system("pause>nul");
    }
};
