/**
 * @file DataHelper.h
 * @brief 数据处理辅助工具类，提供各种数据访问和操作的静态方法
 *
 * @author Skrepy
 * @date 2026/1/7
 */

#pragma once
#include <direct.h>
#include <fstream>
#include <windows.h>

#include "../../source/data/library/json.hpp"
#include "Accommodations.h"
#include "AdminData.h"
#include "StayLog.h"
#include "UserData.h"

/**
 * @class DataHelper
 * @brief 数据处理辅助工具类，提供各种数据访问和操作的静态方法
 *
 * 该类是一个工具类，所有方法均为静态方法，不需要实例化即可使用。
 * 主要负责管理员数据、用户数据、住宿数据、入住记录等数据的统一访问接口。
 */
class DataHelper {
private:
    /**
     * @brief 私有构造函数，防止实例化
     */
    DataHelper() = default;

public:
    /**
     * @brief 获取所有管理员列表
     * @return nlohmann::json 包含所有管理员信息的JSON数组
     */
    static nlohmann::json getAdminList() { return AdminData::getAdminJsonData()["admin"]; }

    /**
     * @brief 根据ID获取指定管理员信息
     * @param id 管理员ID
     * @return nlohmann::json 包含指定管理员信息的JSON对象
     */
    static nlohmann::json getAdmin(const std::string &id) {
        return AdminData::getAdminJsonData()["admin"][AdminData::findAdminById(id)];
    }

    /**
     * @brief 修改管理员密码
     * @param id 管理员ID
     * @param newPassword 新密码
     */
    static void setAdminPassword(const std::string &id, const std::string &newPassword) {
        nlohmann::json admin = getAdmin(id);
        AdminData::deleteAdmin(AdminData::findAdminById(id));
        AdminData(id, newPassword);
    }

    /**
     * @brief 获取所有用户列表
     * @return nlohmann::json 包含所有用户信息的JSON数组
     */
    static nlohmann::json getUserList() { return UserData::readJson()["user"]; }

    /**
     * @brief 根据ID获取指定用户信息
     * @param id 用户ID
     * @return nlohmann::json 包含指定用户信息的JSON对象
     */
    static nlohmann::json getUser(const std::string &id) {
        return UserData::readJson()["user"][UserData::findUserById(id)];
    }

    /**
     * @brief 从用户数据中获取宿舍信息
     * @param userData 用户数据JSON对象
     * @return nlohmann::json 包含宿舍信息的JSON对象
     */
    static nlohmann::json getDormitory(const nlohmann::json &userData) {
        nlohmann::json building = getDormitoryBuildingList()[Accommodations::findBuildingByNumber(userData["dormitory"]["building_number"])];
        if (!building.empty()) {
            for (auto dormitory : building["dormitories"]) {
                if (dormitory["room_number"] == userData["dormitory"]["room_number"]) {
                    return dormitory;
                }
            }
        }
        return nlohmann::json{};
    }

    /**
     * @brief 获取所有宿舍楼列表
     * @return nlohmann::json 包含所有宿舍楼信息的JSON数组
     */
    static nlohmann::json getDormitoryBuildingList() { return Accommodations::readFromJson()["dormitory_building"]; }

    /**
     * @brief 根据哈希值查找入住记录
     * @param type 记录类型，"check-in"表示入住记录，"check-out"表示退房记录
     * @param hash 要查找的哈希值
     * @return int 找到则返回记录索引，未找到返回-1
     */
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

    /**
     * @brief 获取指定目录下的所有文件列表
     * @param directory 目录路径
     * @return std::vector<std::string> 包含所有文件名的向量
     */
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

    /**
     * @brief 获取支持的语言列表
     * @return nlohmann::json 包含所有支持语言的JSON对象
     */
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

    static void writeTempFromJson(const nlohmann::json &data) {
        std::ofstream out_file(R"(..\data\data\temp.json)");
        out_file << data.dump(4);
        out_file.close();
    }
    static nlohmann::json readTempFromJson() {
        std::ifstream in_file(R"(..\data\data\temp.json)");

        nlohmann::json newData = nlohmann::json::parse(in_file);

        in_file.close();
        return newData;
    }
    static nlohmann::json getCheckInApplicationToBeReviewedList() {
        nlohmann::json checkInList = StayLog::readJson()["check-in"];
        nlohmann::json list = nlohmann::json::array();
        for (auto i : checkInList) {
            if (i["status"] == "pending") {
                list.push_back(i);
            }
        }
        return checkInList;
    }
    static nlohmann::json getCheckOutApplicationToBeReviewedList() {
        nlohmann::json checkInList = StayLog::readJson()["check-out"];
        nlohmann::json list = nlohmann::json::array();
        for (auto i : checkInList) {
            if (i["status"] == "pending") {
                list.push_back(i);
            }
        }
        return checkInList;
    }
};
