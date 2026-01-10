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
    std::string bed_count;
    int vacant_bed;
    int stay_log_count;
    int maintenance_count;
    // int maintenances;
    void show() {
        system("cls");
        SelectMenu::hideCursor();
        Message(Text("operation.user.dormitory_info.title.begin")).printContent();
        Message(Text("operation.user.dormitory_info.title")).printContent();
        Message(Text("operation.user.dormitory_info.title.end")).printContent();
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
        Message(Text("operation.user.dormitory_info.info.bed_number").append(bed_count).append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.vacant_bed")
                        .append(Text::intToText(vacant_bed))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.stay_log_count")
                        .append(Text::intToText(stay_log_count))
                        .append(Text::of("$r\n")))
                .printContent();
        Message(Text("operation.user.dormitory_info.info.maintenance_count")
                        .append(Text::intToText(maintenance_count))
                        .append(Text::of("$r\n")))
                .printContent();
    }

public:
    DormitoryInfoScreen() {
        try {
            nlohmann::json dormitory = DataHelper::getDormitory(DataHelper::getUser(DataHelper::readTempFromJson()["id"]));
            user_name = DataHelper::getUser(DataHelper::readTempFromJson()["id"])["name"];
            floor = dormitory["floor"];
            building_name = dormitory["building_name"];
            building_number = dormitory["building_number"];
            bed_count = dormitory["bed_count"];
            room_number = dormitory["room_number"];
            vacant_bed = dormitory["vacant_bed"];
            stay_log_count = 0;
            nlohmann::json stayLogData = StayLog::readJson();
            for (auto i: stayLogData["check-in"]) {
                if (i["dormitory"]["building_number"] == building_number &&
                    i["dormitory"]["building_name"] == building_name && i["dormitory"]["room_number"] == room_number) {
                    stay_log_count++;
                    }
            }
            for (auto i: stayLogData["check-out"]) {
                if (i["dormitory"]["building_number"] == building_number &&
                    i["dormitory"]["building_name"] == building_name && i["dormitory"]["room_number"] == room_number) {
                    stay_log_count++;
                    }
            }
            maintenance_count = static_cast<int>(dormitory["maintenances"].size());
            show();
            system("pause>nul");
        }catch (...) {
            Message(Text::of("operation.user.dormitory_info.error")).printContent();
            system("pause>nul");
        }
    }
};
