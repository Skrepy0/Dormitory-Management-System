#pragma once
#include <iostream>
#include "../../../source/data/library/json.hpp"
#include "./Maintenance.h"
class Dormitory {
private:
    nlohmann::json data;
    std::string building_number; // 楼栋号
    std::string building_name; // 楼栋名称
    std::string floor; // 楼层信息
    std::string room_number; // 宿舍号
    int vacant_bed; // 空床位数
    int total_bed{}; // 总床位数
    nlohmann::json maintenances = nlohmann::json::array(); // json列表储存报修信息
public:
    bool addMaintenances(Maintenance maintenance);

    Dormitory(std::string building_number, std::string building_name, std::string floor, std::string room_number,
              const int vacant_bed, const int total_bed) :
        building_number(std::move(building_number)), building_name(std::move(building_name)), floor(std::move(floor)),
        room_number(std::move(room_number)), vacant_bed(vacant_bed), total_bed(total_bed) {}

    nlohmann::json getDormitoryData();
    long long findMaintenanceById(std::string id); // 通过id查找维修记录并返回索引
    nlohmann::json getUnsettledMaintenanceList(); // 获取未处理的维修记录返回json列表
    std::string getFloor();
    std::string getRoomNumber();
    int getVacantBed() const;
    nlohmann::json getMaintenancesList();

    int getTotalBed() const;

    std::string getBuildingNumber() const;

    void setBuildingNumber(const std::string &building_number);

    std::string getBuildingName() const;

    void setBuildingName(const std::string &building_name);

    void setTotalBed(int total_bed);
};
