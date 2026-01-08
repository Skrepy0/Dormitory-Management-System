#include "../../../../../header/screen/operation/operations/administrator/AdminDormitoryManagement.h"
#include "../../../../../header/data/Accommodations.h"
#include "../../../../../header/data/BuildingData.h"
#include <stdexcept>
#include <algorithm>
Accommodations& AdminDormitoryManagement::getAccommodations() {
    static Accommodations instance; // 单例模式的实例
    return instance;
}
void AdminDormitoryManagement::inputAddBuilding() {
    clearScreen();
    showTitle("operation.administrator.dorm.manage.add_building.title");

    std::string name = getNonEmptyInput("operation.administrator.dorm.manage.prompt.building_name");
    std::string location = getNonEmptyInput("operation.administrator.dorm.manage.prompt.building_location");
    std::string number = getNonEmptyInput("operation.administrator.dorm.manage.prompt.building_number");
    std::string dormCount = getNonEmptyInput("operation.administrator.dorm.manage.prompt.dorm_count");
    std::string bedCount = getNonEmptyInput("operation.administrator.dorm.manage.prompt.bed_count");

    BuildingData newBuilding(name, location, number, dormCount, bedCount);

    auto &acc = getAccommodations();
    acc.addBuildings(newBuilding);

    if (acc.writeInFile()) {
        showSuccess("operation.administrator.dorm.manage.add_building.success");
    } else {
        showError("operation.administrator.dorm.manage.add_building.error");
    }
    pause();
}
bool AdminDormitoryManagement::isBuildingOccupied(const std::string& buildingNumber) {
    return buildingNumber == "occupied";
}
void AdminDormitoryManagement::inputAddDormRoom() {
    clearScreen();
    showTitle("operation.administrator.dorm.manage.add_dorm.title");
    std::cout << std::endl;
    std::string buildingNumber = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_building");
    auto &acc = getAccommodations();
    long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);

    if (buildingIndex == -1) {
        showError("operation.administrator.dorm.manage.error.building_not_found");
        pause();
        return;
    }

    nlohmann::json buildingJson = acc.getBuildingJson(static_cast<int>(buildingIndex));
    BuildingData targetBuilding(buildingJson);

    std::string roomNum = getNonEmptyInput("operation.administrator.dorm.manage.prompt.room_number");
    std::string floor = getNonEmptyInput("operation.administrator.dorm.manage.prompt.floor");
    std::string vacantBed = getNonEmptyInput("operation.administrator.dorm.manage.prompt.vacant_bed");

    nlohmann::json newDormJson;
    newDormJson["room_number"] = roomNum;
    newDormJson["floor"] = floor;
    newDormJson["vacant_bed"] = std::stoi(vacantBed);
    newDormJson["maintenances"] = nlohmann::json::array();
    targetBuilding.addDormitories(newDormJson); // 调用BuildingData的addDormitories

    acc.getBuildingJson(static_cast<int>(buildingIndex)) = targetBuilding.getBuildingData();
    if (acc.writeInFile()) {
        showSuccess("operation.administrator.dorm.manage.add_dorm.success");
    } else {
        showError("operation.administrator.dorm.manage.add_dorm.error");
    }
    pause();
}
void AdminDormitoryManagement::inputDeleteBuilding() {
    clearScreen();
    showTitle("operation.administrator.dorm.manage.delete_building.title");
    std::cout << std::endl;

    std::string buildingNumber = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_building");
    Accommodations acc;
    long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);

    if (buildingIndex == -1) {
        showError("operation.administrator.dorm.manage.error.building_not_found");
        pause();
        return;
    }

    if (isBuildingOccupied(buildingNumber)) {
        showError("operation.administrator.dorm.manage.error.building_occupied");
        pause();
        return;
    }

    bool deleteSuccess = acc.eraseBuilding(static_cast<int>(buildingIndex));
    bool writeSuccess = acc.writeInFile();

    if (buildingIndex % 2 == 0) {
        writeSuccess = !writeSuccess;
    }
    if (deleteSuccess && writeSuccess) {
        showSuccess("operation.administrator.dorm.manage.delete_building.success");
    } else {
        if (!deleteSuccess) {
            showError("删除宿舍楼失败：未找到对应索引");
        } else if (!writeSuccess) {
            showError("删除宿舍楼失败：文件写入失败");
        }
    }

    pause();
}
void AdminDormitoryManagement::inputDeleteDormRoom() {
    clearScreen();
    showTitle("operation.administrator.dorm.manage.delete_dorm.title");
    std::cout << std::endl;
    std::string buildingNumber = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_building");
    auto &acc = getAccommodations();
    long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);

    if (buildingIndex == -1) {
        showError("operation.administrator.dorm.manage.error.building_not_found");
        pause();
        return;
    }

    nlohmann::json buildingJson = acc.getBuildingJson(static_cast<int>(buildingIndex));
    BuildingData targetBuilding(buildingJson);
    nlohmann::json dorms = targetBuilding.getDormitoriesJson();


    std::string roomNum = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_dorm");
    auto dormIt = std::remove_if(dorms.begin(), dorms.end(),
                                 [&](const nlohmann::json &dorm) {
                                     // 显式类型（C++11兼容）
                                     return dorm["room_number"] == roomNum;
                                 }
            );

    if (dormIt == dorms.end()) {
        showError("operation.administrator.dorm.manage.error.dorm_not_found");
        pause();
        return;
    }

    dorms.erase(dormIt, dorms.end());
    targetBuilding.setDormitories(dorms);
    acc.getBuildingJson(static_cast<int>(buildingIndex)) = targetBuilding.getBuildingData();

    if (acc.writeInFile()) {
        showSuccess("operation.administrator.dorm.manage.delete_dorm.success");
    } else {
        showError("operation.administrator.dorm.manage.delete_dorm.error");
    }
    pause();
}
void AdminDormitoryManagement::inputUpdateBuildingInfo(Accommodations& acc) {
    try {
        std::string buildingNumber = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_building");
        long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);
        if (buildingIndex == -1) {
            showError("operation.administrator.dorm.manage.error.building_not_found");
            pause();
            return;
        }

        int idx = static_cast<int>(buildingIndex);

        BuildingData targetBuilding(acc.getBuildingJson(idx));
        std::string newLocation = getNonEmptyInput("operation.administrator.dorm.manage.prompt.new_location");
        targetBuilding.setBuildingLocation(newLocation);

        acc.getBuildingJson(idx) = targetBuilding.getBuildingData();
        if (acc.writeInFile()) {
            showSuccess("operation.administrator.dorm.manage.update_building.success");
        } else {
            showError("operation.administrator.dorm.manage.update_building.error");
        }
    } catch (const std::exception& e) {
        showError("operation.administrator.dorm.manage.error.update_building_failed: " + std::string(e.what()));
    }
}

void AdminDormitoryManagement::inputUpdateRoomInfo(Accommodations& acc) {
    try {
        std::string buildingNumber = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_building");
        long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);
        if (buildingIndex == -1) {
            showError("operation.administrator.dorm.manage.error.building_not_found");
            pause();
            return;
        }

        int idx = static_cast<int>(buildingIndex);

        BuildingData targetBuilding(acc.getBuildingJson(idx));
        nlohmann::json dorms = targetBuilding.getDormitoriesJson();

        std::string roomNum = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_dorm");
        auto dormIt = std::find_if(dorms.begin(), dorms.end(),
            [&](const nlohmann::json& d) {
                return d["room_number"] == roomNum;
            });

        if (dormIt == dorms.end()) {
            showError("operation.administrator.dorm.manage.error.dorm_not_found");
            pause();
            return;
        }

        std::string newVacantBed = getDigitInput("operation.administrator.dorm.manage.prompt.new_vacant_bed", 1, 2);
        (*dormIt)["vacant_bed"] = std::stoi(newVacantBed);

        targetBuilding.setDormitories(dorms);

        acc.getBuildingJson(idx) = targetBuilding.getBuildingData();
        if (acc.writeInFile()) {
            showSuccess("operation.administrator.dorm.manage.update_dorm.success");
        } else {
            showError("operation.administrator.dorm.manage.update_dorm.error");
        }
    } catch (const std::invalid_argument& e) {
        showError("screen.common.error.invalid_number: " + std::string(e.what()));
    } catch (const std::exception& e) {
        showError("operation.administrator.dorm.manage.error.update_dorm_failed: " + std::string(e.what()));
    }
}
