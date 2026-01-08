//
// Created by Skrepy on 2026/1/7.
//

#include "../../header/data/AdminData.h"

#include <direct.h>
#include <fstream>
#include <utility>

#include "../../header/data/HashHelper.h"

// 初始化静态成员变量
nlohmann::json AdminData::data;
// 初始化静态哈希表
std::unordered_map<std::string, int> AdminData::adminIdToIndex;

namespace {
    std::string FILE_PATH;
}

nlohmann::json AdminData::getAdminJsonData() {
    initFilePath();
    std::ifstream in_file(FILE_PATH);

    nlohmann::json newData = nlohmann::json::parse(in_file);

    in_file.close();
    return newData;
}

void AdminData::initFilePath() {
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string frontPath = cwd;
        frontPath.erase(frontPath.size() - 17, 18);
        // 获取当前工作目录成功
        FILE_PATH = frontPath + "data\\data\\Admin.json";
    } else {
        std::cout << "Error: Could not get current working directory" << std::endl;
    }
}

void AdminData::updateData() {
    data = getAdminJsonData();
    admin["id"] = id;
    admin["password"] = HashHelper::getHash(password);
    data["admin"].push_back(admin);

    // 更新哈希表
    adminIdToIndex.clear();
    for (int i = 0; i < data["admin"].size(); i++) {
        adminIdToIndex[data["admin"][i]["id"]] = i;
    }
}

std::string AdminData::getPassword() { return password; }

nlohmann::json AdminData::getAdminData() const { return admin; }

nlohmann::json AdminData::getData() { return data; }

void AdminData::setAdminData(const nlohmann::json &admin) { this->admin = admin; }

std::string AdminData::getId() const { return id; }

void AdminData::setId(std::string id) { this->id = std::move(id); }

void AdminData::setPassword(const std::string &password) { this->password = password; }

bool AdminData::deleteAdmin(int index) {
    try {
        data = getAdminJsonData();

        // 获取要删除的管理员ID
        std::string deletedId = data["admin"][index]["id"];

        // 删除管理员
        data["admin"].erase(data["admin"].begin() + index);

        // 重新构建哈希表，因为索引已经改变
        adminIdToIndex.clear();
        for (int i = 0; i < data["admin"].size(); i++) {
            adminIdToIndex[data["admin"][i]["id"]] = i;
        }

        writeToFile();
        return true;
    } catch (...) {
        return false;
    }
}

int AdminData::findAdminById(std::string id) {
    try {
        if (adminIdToIndex.empty()) {
            data = getAdminJsonData();
            for (int i = 0; i < data["administrator"].size(); i++) {
                adminIdToIndex[data["administrator"][i]["id"]] = i;
            }
        }

        auto it = adminIdToIndex.find(id);
        if (it != adminIdToIndex.end()) {
            return it->second;
        }
        return -1;
    } catch (...) {
        return -1;
    }
}

bool AdminData::writeToFile() {
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return false;
    }
    out_file << data.dump(4);
    out_file.close();
    return true;
}
