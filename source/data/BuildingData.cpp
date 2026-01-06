#include "../../header/data/BuildingData.h"
BuildingData::BuildingData() {}
BuildingData::BuildingData(std::string building_name, std::string building_location, std::string building_number,
                           std::string dormitories_count, std::string bed_count) :
    building_name(building_name), building_location(building_location), building_number(building_number),
    dormitories_count(dormitories_count), bed_count(bed_count) {}

BuildingData::BuildingData(const nlohmann::json &building) {
    building_name = building["building_name"];
    building_location = building["building_location"];
    building_number = building["building_number"];
    dormitories_count = building["dormitories_count"];
    bed_count = building["bed_count"];
    dormitories = building["dormitories"];
}

bool BuildingData::setDormitories(nlohmann::json dormitories) {
    if (!dormitories.is_array())
        return false;
    this->dormitories = dormitories;
    return true;
}
bool BuildingData::addDormitory(Dormitory dormitory) {
    try {
        dormitories.push_back(dormitory.getDormitoryData());
        return true;
    } catch (...) {
        return false;
    }
}
bool BuildingData::addDormitories(nlohmann::json dormitoriesList) {
    if (!dormitoriesList.is_array())
        return false;
    for (auto i: dormitoriesList) {
        this->dormitories.push_back(i);
    }
    return true;
}
nlohmann::json BuildingData::getBuildingData() {
    data["building_number"] = building_number;
    data["building_location"] = building_location;
    data["dormitories_count"] = dormitories_count;
    data["bed_count"] = bed_count;
    data["dormitories"] = dormitories;
    data["building_name"] = building_name;
    return data;
}

std::string BuildingData::getBuildingName() { return building_name; }

std::string BuildingData::getBuildingLocation() { return building_location; }

std::string BuildingData::getBuildingNumber() { return building_number; }

std::string BuildingData::getDormitoriesCount() { return dormitories_count; }

std::string BuildingData::getBedCount() { return bed_count; }

nlohmann::json BuildingData::getDormitoriesJson() { return dormitories; }

void BuildingData::setBuildingData(nlohmann::json buildingData) { data = buildingData; }

void BuildingData::setBuildingName(std::string name) { building_name = name; }

void BuildingData::setBuildingLocation(std::string location) { building_location = location; }

void BuildingData::setBuildingNumber(std::string number) { building_number = number; }

void BuildingData::setDormitoriesCount(std::string count) { dormitories_count = count; }

void BuildingData::setBedCount(std::string count) { bed_count = count; }
