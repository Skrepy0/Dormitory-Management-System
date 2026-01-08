#include "../../../header/data/basic/Dormitory.h"
#include <iostream>
#include <utility>

bool Dormitory::addMaintenances(Maintenance maintenance) {
    try {
        maintenances.push_back(maintenance.getMaintenanceData());
        return true;
    } catch (...) {
        return false;
    }
}

nlohmann::json Dormitory::getDormitoryData() {
    data["building_number"] = building_number;
    data["building_name"] = building_name;
    data["floor"] = floor;
    data["room_number"] = room_number;
    data["vacant_bed"] = vacant_bed;
    data["maintenances"] = maintenances;
    data["total_bed"] = total_bed;
    return this->data;
}

long long Dormitory::findMaintenanceById(std::string id) {
    if (maintenances.empty())
        return -1;
    else {
        int index = 0;
        for (auto i: maintenances) {
            if (id == (std::string) i["id"]) {
                return index;
            }
            index++;
        }
    }
    return -1;
}

nlohmann::json Dormitory::getUnsettledMaintenanceList() {
    nlohmann::json jsonList = nlohmann::json::array();
    for (auto i: maintenances) {
        if ((bool) i["state"])
            jsonList.push_back(i);
    }
    return jsonList;
}

std::string Dormitory::getFloor() { return floor; }

std::string Dormitory::getRoomNumber() { return room_number; }

int Dormitory::getVacantBed() const { return vacant_bed; }

nlohmann::json Dormitory::getMaintenancesList() { return maintenances; }

int Dormitory::getTotalBed() const { return total_bed; }

std::string Dormitory::getBuildingNumber() const { return building_number; }

void Dormitory::setBuildingNumber(const std::string &building_number) { this->building_number = building_number; }

std::string Dormitory::getBuildingName() const { return building_name; }

void Dormitory::setBuildingName(const std::string &building_name) { this->building_name = building_name; }
void Dormitory::setTotalBed(int total) { this->total_bed = total; }
// 补充：修改空床位数
void Dormitory::setVacantBed(int newVacantBed) {vacant_bed = newVacantBed;}
