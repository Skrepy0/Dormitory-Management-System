//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include "UserData.h"
#include "../../source/data/library/json.hpp"

class DataHelper {
private:
    DataHelper() = default;

public:
    static nlohmann::json getUserList() {
        return UserData::readJson()["user"];
    }

    static nlohmann::json getUser(const std::string &id) {
        return UserData::readJson()["user"][UserData::findUserById(id)];
    }

    static nlohmann::json getDormitory(const nlohmann::json &userData) {
        return userData["dormitory"];
    }

    static nlohmann::json getDormitoryBuildingList() {
        return Accommodations::readFromJson()["dormitory_building"];
    }
};
