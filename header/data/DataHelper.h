//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include <direct.h>
#include <fstream>

#include "../../source/data/library/json.hpp"
#include "Accommodations.h"
#include "AdminData.h"
#include "UserData.h"

class DataHelper {
private:
    DataHelper() = default;

public:
    static nlohmann::json getAdminList() { return AdminData::getAdminJsonData()["admin"]; }

    static nlohmann::json getAdmin(const std::string &id) {
        return AdminData::getAdminJsonData()["admin"][AdminData::findAdminById(id)];
    }

    static void setAdminPassword(const std::string &id, const std::string &newPassword) {
        nlohmann::json admin = getAdmin(id);
        AdminData::deleteAdmin(AdminData::findAdminById(id));
        AdminData(id, newPassword);
    }

    static nlohmann::json getUserList() { return UserData::readJson()["user"]; }

    static nlohmann::json getUser(const std::string &id) {
        return UserData::readJson()["user"][UserData::findUserById(id)];
    }

    static nlohmann::json getDormitory(const nlohmann::json &userData) { return userData["dormitory"]; }

    static nlohmann::json getDormitoryBuildingList() { return Accommodations::readFromJson()["dormitory_building"]; }
};
