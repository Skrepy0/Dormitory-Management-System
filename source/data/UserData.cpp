#include "../../header/data/UserData.h"
#include <direct.h>
#include <fstream>
#include <iostream>
#include <utility>
#include "../../header/data/BuildingData.h"
#include "../../header/data/HashHelper.h"
namespace {
    std::string FILE_PATH;
    void initFilePath() {
        char cwd[1024];
        if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
            std::string frontPath = cwd;
            frontPath.erase(frontPath.size() - 17, 18);
            // 获取当前工作目录成功
            FILE_PATH = frontPath + "data\\data\\UserData.json";
        } else {
            std::cout << "Error: Could not get current working directory" << std::endl;
        }
    }
} // namespace


void UserData::init() {
    initFilePath();
    data = UserData::readJson();
}

void UserData::addToData() {
    nlohmann::json newData;
    newData["name"] = name;
    newData["password"] = HashHelper::simpleHashString(password);
    newData["email"] = email;
    newData["id"] = id;

    nlohmann::json dormitoryData;
    dormitoryData["bed_number"] = dormitory.getTotalBed();
    dormitoryData["building_number"] = dormitory.getBuildingNumber();
    dormitoryData["room_number"] = dormitory.getRoomNumber();
    dormitoryData["building_name"] = dormitory.getBuildingName();
    dormitoryData["vacant_bed"] = dormitory.getVacantBed();
    dormitoryData["floor"] = dormitory.getFloor();
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
    initFilePath();
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

UserData::UserData(std::string name, std::string id, std::string password, std::string email, Dormitory dormitory) :
    name(std::move(name)), id(std::move(id)), password(password), email(email), dormitory(std::move(dormitory)) {
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
