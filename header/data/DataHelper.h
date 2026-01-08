//
// Created by Skrepy on 2026/1/7.
//
#pragma once
#include <direct.h>
#include <fstream>
#include <windows.h>

#include "../../source/data/library/json.hpp"
#include "Accommodations.h"
#include "AdminData.h"
#include "StayLog.h"
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

    static int findStayLogByHash(const std::string &type, const std::string &hash) {
        nlohmann::json json;
        if (type == "check-in") {
            json = StayLog::getCheckInRecords();
        } else if (type == "check-out") {
            json = StayLog::getCheckOutRecords();
        }
        for (int i = 0; i < json.size(); i++) {
            if (json[i]["hash"] == hash) {
                return i;
            }
        }
        return -1;
    }

    static std::vector<std::string> getFileListInDirectory(const std::string &directory) {
        std::vector<std::string> files;
        std::string search_path = directory + "/*.*";
        WIN32_FIND_DATA fd;
        HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);

        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                // 读取文件名
                std::string name = fd.cFileName;

                // 过滤 . 和 ..
                if (name != "." && name != "..") {
                    // dwFileAttributes 属性位判断是否为目录
                    if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                        files.push_back(name);
                    }
                }
            } while (FindNextFile(hFind, &fd));
            FindClose(hFind);
        }

        return files;
    }
    static nlohmann::json getLanguageList() {
        std::ifstream in_file(R"(..\data\lang\language.json)");
        if (!in_file.is_open()) {
            return nlohmann::json{};
        }
        nlohmann::json langData;
        in_file >> langData;
        in_file.close();
        return langData["languages"];
    }
};
