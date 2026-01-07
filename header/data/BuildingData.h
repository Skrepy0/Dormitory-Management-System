#pragma once
#include <iostream>
#include "../../source/data/library/json.hpp"
#include "./basic/Dormitory.h"
class BuildingData {
private:
    nlohmann::json data; // 宿舍数据
    std::string building_name; // 宿舍楼名字
    std::string building_location; // 宿舍楼位置信息
    std::string building_number; // 楼号
    std::string dormitories_count; // 宿舍数量
    std::string bed_count; // 每个宿舍的床位数量
    nlohmann::json dormitories = nlohmann::json::array(); // 宿舍列表

public:
    BuildingData();
    BuildingData(std::string building_name, std::string building_location, std::string building_number,
                 std::string dormitories_count, std::string bed_count);
    BuildingData(const nlohmann::json &);
    bool setDormitories(nlohmann::json dormitories); // 传参是json列表,返回是否设置成功
    bool addDormitory(Dormitory dormitory); // 添加宿舍
    bool addDormitories(nlohmann::json dormitoriesList); // 添加宿舍(批量添加)
    // 这里不提供删除方法了:(

    nlohmann::json getBuildingData();
    std::string getBuildingName();
    std::string getBuildingLocation();
    std::string getBuildingNumber();
    std::string getDormitoriesCount();
    std::string getBedCount();
    nlohmann::json getDormitoriesJson();

    void setBuildingData(nlohmann::json buildingData);
    void setBuildingName(std::string name);
    void setBuildingLocation(std::string location);
    void setBuildingNumber(std::string number);
    void setDormitoriesCount(std::string count);
    void setBedCount(std::string count);
    nlohmann::json readAllBuildings();
};
