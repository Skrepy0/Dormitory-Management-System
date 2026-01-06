#include "../../header/data/UserData.h"
#include <direct.h>
#include <fstream>
#include <iostream>
#include "../../header/data/BuildingData.h"
namespace {
    std::string FILE_PATH;
}

void UserData::init() {

    FILE_PATH = R"(..\data\data\UserData.json)";


    data = UserData::readJson();
}

void UserData::addToData() {
    nlohmann::json newData;
    newData["name"] = name;
    newData["password"] = getHash(password);
    newData["email"] = email;
    newData["id"] = id;

    nlohmann::json dormitoryData;
    dormitoryData["bed_number"] = bed_number;
    dormitoryData["building_number"] = building_number;
    dormitoryData["room_number"] = room_number;

    newData["dormitory"] = dormitoryData;

    // 确保user数组存在
    if (!data.contains("user") || !data["user"].is_array()) {
        data["user"] = nlohmann::json::array();
    }

    data["user"].push_back(newData);

    writeToFile();
}

bool UserData::compareDormitory(nlohmann::json dormitory_1, nlohmann::json dormitory_2) {
    if (dormitory_1["room_number"] != dormitory_2["room_number"])
        return false;
    if (dormitory_1["bed_number"] != dormitory_2["bed_number"])
        return false;
    if (dormitory_1["building_number"] != dormitory_2["building_number"])
        return false;
    return true;
}

size_t UserData::getHash(std::string str) {
    std::hash<std::string> hasher;
    size_t hash_value = hasher(str);
    return hash_value;
}

void UserData::addFromJson(nlohmann::json userData) {
    // 验证输入数据
    if (userData.is_null()) {
        std::cerr << "Error: Cannot add null user data!" << std::endl;
        return;
    }
    nlohmann::json jsonData = readJson();
    // 确保user数组存在
    if (!jsonData.contains("user") || !jsonData["user"].is_array()) {
        jsonData["user"] = nlohmann::json::array();
    }

    jsonData["user"].push_back(userData);
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return;
    }
    out_file << jsonData.dump(4);
    out_file.close();
}

nlohmann::json UserData::getData() { return data; }

void UserData::setData(nlohmann::json userData) {
    if (!userData.is_null()) {
        data = userData;
    } else {
        std::cerr << "Warning: Attempting to set null data, operation ignored." << std::endl;
    }
}

nlohmann::json UserData::readJson() {
    std::ifstream in_file(FILE_PATH);

    nlohmann::json newData = nlohmann::json::parse(in_file);
    // 确保数据有正确的结构
    if (!newData.contains("user") || !newData["user"].is_array()) {
        newData["user"] = nlohmann::json::array();
    }

    in_file.close();
    return newData;
}

long long UserData::findUserByName(std::string name) {
    nlohmann::json allData = UserData::readJson();
    auto array = allData["user"];
    for (long long i = 0; i < array.size(); ++i) {
        if ((std::string) array[i]["name"] == name)
            return i;
    }
    return -1;
}

long long UserData::findUserById(std::string id) {
    nlohmann::json allData = UserData::readJson();
    auto array = allData["user"];
    for (long long i = 0; i < array.size(); ++i) {
        if ((std::string) array[i]["id"] == id)
            return i;
    }
    return -1;
}

long long UserData::findUserByDormitory(nlohmann::json dormitory) {
    nlohmann::json allData = UserData::readJson();
    auto array = allData["user"];
    for (long long i = 0; i < array.size(); ++i) {

        if (compareDormitory(array[i]["dormitory"], dormitory))
            return i;
    }
    return -1;
}

bool UserData::eraseUserById(std::string id) {
    try {
        nlohmann::json allData = readJson();
        auto array = allData["user"];
        long long index = findUserById(id);
        if (index != -1) {
            array.erase(index);
            std::ofstream out_file(FILE_PATH);
            if (!out_file.is_open()) {
                return false;
            }
            nlohmann::json newData;
            newData["user"] = array;
            out_file << newData.dump(4);
            out_file.close();
            return true;
        }
        return false;
    } catch (...) {
        return false;
    }
}

bool UserData::eraseUserByDormitory(nlohmann::json dormitory) {
    nlohmann::json allData = readJson();
    auto array = allData["user"];
    long long index = findUserByDormitory(dormitory);
    if (index != -1) {
        array.erase(index);
        std::ofstream out_file(FILE_PATH);
        if (!out_file.is_open()) {
            return false;
        }
        nlohmann::json newData;
        newData["user"] = array;
        out_file << newData.dump(4);
        out_file.close();
        return true;
    }
    return false;
}

UserData::UserData() { init(); }

UserData::UserData(std::string name, std::string id, std::string password, std::string email,
                   std::string building_number, std::string room_number, std::string bed_number) :
    name(name), id(id), password(password), email(email), building_number(building_number), room_number(room_number),
    bed_number(bed_number) {
    init();
    addToData();
    writeToFile();
}
bool UserData::writeToFile() {
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return false;
    }
    out_file << data.dump(4);
    out_file.close();
    return true;
}
