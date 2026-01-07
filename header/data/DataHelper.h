//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include <direct.h>
#include <fstream>

#include "UserData.h"
#include "../../source/data/library/json.hpp"

class DataHelper {
private:
    DataHelper() = default;


public:
    static nlohmann::json getAdminData() {
        std::string FILE_PATH;
        char cwd[1024];
        if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::string frontPath = cwd;
            frontPath.erase(frontPath.size() - 17, 18);
            // 获取当前工作目录成功
            FILE_PATH = frontPath + "data\\data\\Admin.json";
        } else {
            std::cout << "Error: Could not get current working directory" << std::endl;
        }
        std::ifstream in_file(FILE_PATH);

        nlohmann::json newData = nlohmann::json::parse(in_file);

        in_file.close();
        return newData;
    }

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
