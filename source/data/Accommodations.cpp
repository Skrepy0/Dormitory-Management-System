#include<iostream>
#include<fstream>
#include<direct.h>
#include <unordered_map>
#include<stdexcept> // 用于异常处理
#include"../../header/data/Accommodations.h"
#include"../../source/data/library/json.hpp"

namespace {
    std::string FILE_PATH;
}

// 静态成员初始化
std::unordered_map<std::string, long long> Accommodations::locationIndexMap;
std::unordered_map<std::string, long long> Accommodations::nameIndexMap;
std::unordered_map<std::string, long long> Accommodations::numberIndexMap;

void Accommodations::init() {
    FILE_PATH = R"(..\data\data\DormitoryData.json)";
    // 确保目录存在（避免文件写入失败）
    std::string dir = R"(..\data\data)";
    _mkdir(dir.c_str()); // Windows下创建目录，Linux用mkdir
}

nlohmann::json Accommodations::readFromJson() {
    std::ifstream in_file(FILE_PATH);
    nlohmann::json newData;
    if (in_file.is_open()) {
        try {
            newData = nlohmann::json::parse(in_file);
        } catch (const nlohmann::json::parse_error& e) {
            // 解析失败时初始化空数组
            newData = nlohmann::json::object();
        }
        in_file.close();
    } else {
        // 文件不存在时初始化空对象
        newData = nlohmann::json::object();
    }
    // 确保dormitory_building是数组
    if (!newData.contains("dormitory_building") || !newData["dormitory_building"].is_array()) {
        newData["dormitory_building"] = nlohmann::json::array();
    }
    return newData;
}

bool Accommodations::writeInFile() {
    return writeInFile(this->data);
}

bool Accommodations::writeInFile(nlohmann::json data) {
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return false;
    }
    out_file << data.dump(4);
    out_file.close();
    buildIndexMaps();
    return true;
}

nlohmann::json Accommodations::getBuildingJson(int index) {
    if (index >= 0 && static_cast<size_t>(index) < data["dormitory_building"].size()) {
        return data["dormitory_building"][index];
    }
    return nlohmann::json();
}

void Accommodations::buildIndexMaps() {
    locationIndexMap.clear();
    nameIndexMap.clear();
    numberIndexMap.clear();
    nlohmann::json j = readFromJson(); // 直接使用当前数据，避免重复读文件
    size_t idx = 0; // 用size_t避免类型不匹配
    for (auto &b: j["dormitory_building"]) {
        // 安全获取JSON值（避免类型转换异常）
        auto get_str = [&](const std::string& key) -> std::string {
            if (b.contains(key) && b[key].is_string()) {
                return b[key].get<std::string>();
            }
            return "";
        };
        std::string loc = get_str("building_location");
        std::string name = get_str("building_name");
        std::string num = get_str("building_number");

        if (!loc.empty() && locationIndexMap.find(loc) == locationIndexMap.end()) {
            locationIndexMap.emplace(loc, static_cast<long long>(idx));
        }
        if (!name.empty() && nameIndexMap.find(name) == nameIndexMap.end()) {
            nameIndexMap.emplace(name, static_cast<long long>(idx));
        }
        if (!num.empty() && numberIndexMap.find(num) == numberIndexMap.end()) {
            numberIndexMap.emplace(num, static_cast<long long>(idx));
        }
        idx++;
    }
}

Accommodations::Accommodations() {
    init();
    // 直接读取文件数据，无需提前初始化
    data = readFromJson();
    buildIndexMaps();
}

void Accommodations::addBuildings(BuildingData data) {
    nlohmann::json bd = data.getBuildingData();
    this->data["dormitory_building"].push_back(bd);
    // 安全更新索引
    size_t newIndex = this->data["dormitory_building"].size() - 1;
    auto get_str = [&](const std::string& key) -> std::string {
        if (bd.contains(key) && bd[key].is_string()) {
            return bd[key].get<std::string>();
        }
        return "";
    };
    std::string loc = get_str("building_location");
    std::string name = get_str("building_name");
    std::string num = get_str("building_number");

    if (!loc.empty() && locationIndexMap.find(loc) == locationIndexMap.end()) {
        locationIndexMap.emplace(loc, static_cast<long long>(newIndex));
    }
    if (!name.empty() && nameIndexMap.find(name) == nameIndexMap.end()) {
        nameIndexMap.emplace(name, static_cast<long long>(newIndex));
    }
    if (!num.empty() && numberIndexMap.find(num) == numberIndexMap.end()) {
        numberIndexMap.emplace(num, static_cast<long long>(newIndex));
    }
}

long long Accommodations::findBuildingByName(std::string name) {
    if (nameIndexMap.empty()) buildIndexMaps();
    auto it = nameIndexMap.find(name);
    return it != nameIndexMap.end() ? it->second : -1;
}

long long Accommodations::findBuildingByNumber(std::string number) {
    if (numberIndexMap.empty()) buildIndexMaps();
    auto it = numberIndexMap.find(number);
    return it != numberIndexMap.end() ? it->second : -1;
}

long long Accommodations::findBuildingByLocation(std::string location) {
    if (locationIndexMap.empty()) buildIndexMaps();
    auto it = locationIndexMap.find(location);
    return it != locationIndexMap.end() ? it->second : -1;
}

bool Accommodations::eraseBuilding(long long index) {
    auto& array = this->data["dormitory_building"]; // 引用，而非拷贝
    if (index < 0 || static_cast<size_t>(index) >= array.size()) {
        return false;
    }
    array.erase(array.begin() + index);
    return writeInFile(data);
}

bool Accommodations::eraseBuilding(long long begin, long long end) {
    auto& array =  this->data["dormitory_building"];
    if (begin < 0 || end < 0 || static_cast<size_t>(begin) >= array.size() || static_cast<size_t>(end) > array.size() || begin >= end) {
        return false;
    }
    array.erase(array.begin() + begin, array.begin() + end);
    return writeInFile(data);
}

bool Accommodations::clearBuildingList() {
    try {
        nlohmann::json data = this->data;
        auto& array = data["dormitory_building"];
        eraseBuilding(0,array.size());
        return true;
    }catch (...) {
        return false;
    }
}
