//
// Created by Skrepy on 2026/1/7.
//
#include <iostream>
#include <unordered_map>
#include "../../source/data/library/json.hpp"
#pragma once
class AdminData {
private:
    static nlohmann::json data;
    nlohmann::json admin;
    std::string id{};
    std::string password;
    static void initFilePath();
    void updateData();
    static std::unordered_map<std::string, int> adminIdToIndex; // id到索引的映射，实现O(1)查询
public:
    AdminData() {
        initFilePath();
        updateData();
    }
    AdminData(std::string id, const std::string &password) : id(id), password(password) {
        initFilePath();
        updateData();
        writeToFile();
    }
    std::string getPassword();

    nlohmann::json getAdminData() const;
    nlohmann::json getData();
    void setAdminData(const nlohmann::json &admin);

    std::string getId() const;

    void setId(std::string id);

    void setPassword(const std::string &password);
    static bool deleteAdmin(int index);
    static bool addAdmin(nlohmann::json adminData);
    static int findAdminById(std::string id); // 返回值是索引值
    static bool writeToFile();
    static nlohmann::json getAdminJsonData();
};
