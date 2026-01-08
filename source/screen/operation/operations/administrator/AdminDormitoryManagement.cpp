#include "../../../../../header/screen/operation/operations/administrator/AdminDormitoryManagement.h"
#include <algorithm>

using json = nlohmann::json;

void AdminDormitoryManagement::inputAddBuilding() {
    clearScreen();
    showTitle("operation.administrator.dormitory_manage.add_building.title");

    std::string name = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.name");
    std::string location = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.location");
    std::string number = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.building_number");
    std::string dormCount = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.dorm_count");
    std::string bedCount = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.bed_count");

    BuildingData newBuilding(name, location, number, dormCount, bedCount);


    showSuccess("operation.administrator.dormitory_manage.add_building.success");
    pause();
}

void AdminDormitoryManagement::inputAddDorm() {
    clearScreen();
    showTitle("operation.administrator.dormitory_manage.add_dorm.title");

    std::string buildingNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_building");
    BuildingData targetBuilding = getBuildingByNumber(buildingNum);

    if (targetBuilding.getBuildingNumber().empty()) {
        showError("operation.administrator.dormitory_manage.error.building_not_found");
        pause();
        return;
    }

    int addCount = std::stoi(getNonEmptyInput("operation.administrator.dormitory_manage.prompt.add_count"));
    json dormList = json::array();
    for (int i = 0; i < addCount; i++) {
        json newDorm;
        newDorm["room_number"] = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.room_number");
        newDorm["floor"] = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.floor");
        newDorm["vacant_bed"] =
                std::stoi(getNonEmptyInput("operation.administrator.dormitory_manage.prompt.vacant_bed"));
        newDorm["maintenances"] = json::array(); // 初始化维修记录
        dormList.push_back(newDorm);
    }

    targetBuilding.addDormitories(dormList);


    showSuccess("operation.administrator.dormitory_manage.add_dorm.success");
    pause();
}

void AdminDormitoryManagement::inputUpdateBuilding() {
    clearScreen();
    showTitle("operation.administrator.dormitory_manage.update_building.title");
    std::string buildingNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_building");
    BuildingData targetBuilding = getBuildingByNumber(buildingNum);

    if (targetBuilding.getBuildingNumber().empty()) {
        showError("operation.administrator.dormitory_manage.error.building_not_found");
        pause();
        return;
    }

    showPrompt("operation.administrator.dormitory_manage.prompt.update_field");
    std::string choice = getDigitInput("screen.common.input.choice", 1, 1);

    if (choice == "1") {
        std::string newName = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.new_name");
        targetBuilding.setBuildingName(newName); // 调用set方法
    } else if (choice == "2") {
        std::string newLoc = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.new_location");
        targetBuilding.setBuildingLocation(newLoc); // 调用set方法
    }

    showSuccess("operation.administrator.dormitory_manage.update_building.success");
    pause();
}

void AdminDormitoryManagement::inputUpdateDormBed() {
    clearScreen();
    showTitle("operation.administrator.dormitory_manage.update_dorm_bed.title");

    std::string buildingNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_building");
    BuildingData targetBuilding = getBuildingByNumber(buildingNum);

    if (targetBuilding.getBuildingNumber().empty()) {
        showError("operation.administrator.dormitory_manage.error.building_not_found");
        pause();
        return;
    }

    std::string roomNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_dorm");
    json dormList = targetBuilding.getDormitoriesJson();
    targetBuilding.setDormitories(dormList);

    for (auto &dorm: dormList) {
        if (dorm["room_number"] == roomNum) {
            int newBed = std::stoi(getNonEmptyInput("operation.administrator.dormitory_manage.prompt.new_vacant_bed"));
            if (newBed < 0) {
                showError("operation.administrator.dormitory_manage.error.vacant_bed_negative");
                pause();
                return;
            }
            dorm["vacant_bed"] = newBed;
            break;
        }
    }

    showSuccess("operation.administrator.dormitory_manage.update_dorm_bed.success");
    pause();
}


void AdminDormitoryManagement::inputDeleteDorm() {
    clearScreen();
    showTitle("operation.administrator.dormitory_manage.delete_dorm.title");

    std::string buildingNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_building");
    BuildingData targetBuilding = getBuildingByNumber(buildingNum);

    if (targetBuilding.getBuildingNumber().empty()) {
        showError("operation.administrator.dormitory_manage.error.building_not_found");
        pause();
        return;
    }

    std::string roomNum = getNonEmptyInput("operation.administrator.dormitory_manage.prompt.select_dorm");
    json dormList = targetBuilding.getDormitoriesJson();
    targetBuilding.setDormitories(dormList);
    auto it = std::remove_if(dormList.begin(), dormList.end(),
                             [&](const json &dorm) { return dorm["room_number"] == roomNum; });

    if (it == dormList.end()) {
        showError("operation.administrator.dormitory_manage.error.dorm_not_found");
        pause();
        return;
    }

    showSuccess("operation.administrator.dormitory_manage.delete_dorm.success");
    pause();
}
