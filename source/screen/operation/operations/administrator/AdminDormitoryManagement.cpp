#include "../../../../../header/screen/operation/operations/administrator/AdminDormitoryManagement.h"
#include <algorithm>
#include <stdexcept>
#include "../../../../../header/data/Accommodations.h"
#include "../../../../../header/data/BuildingData.h"
#include "../../../../../header/data/DataHelper.h"

Accommodations &AdminDormitoryManagement::getAccommodations() {
    static Accommodations instance;
    return instance;
}
void AdminDormitoryManagement::inputAddBuilding() {
    clearScreen();
    showTitle("operation.administrator.dorm.manage.add_building.title");
    std::cout << std::endl;
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
bool AdminDormitoryManagement::isBuildingOccupied(const std::string &buildingNumber) {
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
    newDormJson["building_number"] = buildingNumber;
    newDormJson["building_name"] = buildingJson["building_name"];
    newDormJson["room_number"] = roomNum;
    newDormJson["bed_count"] = buildingJson["bed_count"];
    newDormJson["floor"] = floor;
    newDormJson["vacant_bed"] = std::stoi(vacantBed);
    newDormJson["maintenances"] = nlohmann::json::array();
    nlohmann::json dormList;
    dormList.push_back(newDormJson);
    targetBuilding.addDormitories(dormList);
    acc.eraseBuilding(static_cast<int>(buildingIndex));
    acc.addBuildings(targetBuilding.getBuildingData());
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
            showError("operation.administrator.dorm.manage.delete_building.error.reason1");
        } else if (!writeSuccess) {
            showError("operation.administrator.dorm.manage.delete_building.error.reason2");
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
    nlohmann::json dorms = buildingJson["dormitories"];


    std::string roomNum = getNonEmptyInput("operation.administrator.dorm.manage.prompt.select_dorm");
    bool flag = false;
    for (auto it = dorms.begin(); it != dorms.end(); ++it) {
        if ((*it)["room_number"].get<std::string>() == roomNum) {
            dorms.erase(it);
            flag = true;
            break;
        }
    }

    if (!flag) {
        showError("operation.administrator.dorm.manage.error.dorm_not_found");
        pause();
        return;
    }

    targetBuilding.setDormitories(dorms);
    acc.eraseBuilding(static_cast<int>(buildingIndex));
    acc.addBuildings(targetBuilding.getBuildingData());
    if (acc.writeInFile()) {
        showSuccess("operation.administrator.dorm.manage.delete_dorm.success");
    } else {
        showError("operation.administrator.dorm.manage.delete_dorm.error");
    }
    pause();
}
void AdminDormitoryManagement::showBuildingCurrentInfo() {
    clearScreen();
    showTitle("admin.dorm.update.building.title.detail");
    std::cout << std::endl;
    std::string targetBuildingNum = getDigitInput(
        "admin.dorm.update.building.prompt.input_building_num",
        1, 3
    );
    nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
    auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
        [&](const nlohmann::json& b) { return b["building_number"] == targetBuildingNum; });

    if (buildingIt == allBuildings.end()) {
        showError(Text("admin.dorm.error.building_not_found").getContent());
    } else {
        showContent("admin.dorm.label.bed_count");
        showContent((*buildingIt)["bed_count"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.building_num");
        showContent((*buildingIt)["building_number"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.building_name");
        showContent((*buildingIt)["building_name"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.building_location");
        showContent((*buildingIt)["building_location"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.dormitories_count");
        showContent((*buildingIt)["dormitories_count"]);
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------" << std::endl;
    pause();
}
void AdminDormitoryManagement::showDormCurrentInfo() {
    clearScreen();
    showTitle("admin.dorm.update.dorm.title.detail");
    std::cout << std::endl;
    std::string targetBuildingNum = getDigitInput(
        "admin.dorm.update.dorm.prompt.input_building_num",
        1, 3
    );
    nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
    auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
        [&](const nlohmann::json& b) { return b["building_number"] == targetBuildingNum; });

    if (buildingIt == allBuildings.end()) {
        showError(Text("admin.dorm.error.building_not_found").getContent());
        pause();
        return;
    }
    std::string targetRoomNum = getDigitInput(
        "admin.dorm.update.dorm.prompt.input_room_num",
        3, 4
    );
    nlohmann::json& dormList = (*buildingIt)["dormitories"];
    auto dormIt = std::find_if(dormList.begin(), dormList.end(),
        [&](const nlohmann::json& d) { return d["room_number"] == targetRoomNum; });

    if (dormIt == dormList.end()) {
        showError(Text("admin.dorm.error.dorm_not_found").getContent());
        pause();
        return;
    }
    nlohmann::json maintenances = (*dormIt)["maintenances"];
    nlohmann::json latestMaintenance;
    bool hasMaintenance = false;

    if (!maintenances.empty()) {
        std::sort(maintenances.begin(), maintenances.end(), [](const nlohmann::json& a, const nlohmann::json& b) {
            const auto& aTime = a["report_time"];
            const auto& bTime = b["report_time"];
            if (aTime["year"] != bTime["year"]) return aTime["year"] > bTime["year"];
            if (aTime["month"] != bTime["month"]) return aTime["month"] > bTime["month"];
            if (aTime["day"] != bTime["day"]) return aTime["day"] > bTime["day"];
            if (aTime["hour"] != bTime["hour"]) return aTime["hour"] > bTime["hour"];
            if (aTime["minute"] != bTime["minute"]) return aTime["minute"] > bTime["minute"];
            return aTime["second"] > bTime["second"];
        });
        latestMaintenance = maintenances[0];
        hasMaintenance = true;
    }

    showContent("admin.dorm.label.building_num");
    showContent(targetBuildingNum);
    std::cout << std::endl;

    showContent("admin.dorm.label.room_num");
    showContent((*dormIt)["room_number"]);
    std::cout << std::endl;

    showContent("admin.dorm.label.total_bed");
    showContent((*dormIt)["total_bed"]);
    std::cout << std::endl;

    showContent("admin.dorm.label.vacant_bed");
    std::cout << static_cast<int>((*dormIt)["vacant_bed"]) << std::endl;

    showContent("admin.dorm.label.latest_maintenance_title");
    std::cout << std::endl;

    if (hasMaintenance) {
        showContent("admin.dorm.label.maintenance_sponsor");
        showContent(latestMaintenance["sponsor"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.maintenance_desc");
        showContent(latestMaintenance["description"]);
        std::cout << std::endl;
        showContent("admin.dorm.label.maintenance_state");
        showContent(latestMaintenance["state"] ? "已完成" : "未完成");
        std::cout << std::endl;
    } else {
        showContent("admin.dorm.label.no_maintenance");
        std::cout << std::endl;
    }

    std::cout << "----------------------------------------" << std::endl;
    pause();
}
void AdminDormitoryManagement::updateDormitoryBuilding() {
    clearScreen();
    showTitle("admin.dorm.update.building.title");
    std::cout << std::endl;
    try {
        showPrompt("admin.dorm.update.prompt.view_before_update");
        pause();
        showBuildingCurrentInfo();
        clearScreen();
        std::string targetBuildingNum = getDigitInput(
            "admin.dorm.update.building.prompt.input_building_num_update",
            1, 3
        );
        nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
        auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
            [&](const nlohmann::json& b) { return b["building_number"] == targetBuildingNum; });

        if (buildingIt == allBuildings.end()) {
            showError(Text("admin.dorm.error.building_not_found").getContent());
            pause();
            return;
        }
        std::string newName = getNonEmptyInput("admin.dorm.update.building.prompt.input_new_name");

        std::string newLocation = getNonEmptyInput("admin.dorm.update.building.prompt.input_new_location");

        std::string newDormCountStr = getDigitInput("admin.dorm.update.building.prompt.input_new_dorm_count", 1, 999);

        std::string newBedCountStr = getDigitInput("admin.dorm.update.building.prompt.input_new_bed_count", 1, 8);
        bool hasChange = false;
        if (!newName.empty()) hasChange = true;
        if (!newLocation.empty()) hasChange = true;
        if (!newDormCountStr.empty()) hasChange = true;
        if (!newBedCountStr.empty()) hasChange = true;

        if (!hasChange) {
            showPrompt("admin.dorm.update.prompt.no_change");
            pause();
            return;
        }
        if (!confirmOperation("admin.dorm.update.prompt.confirm")) {
            showPrompt("admin.dorm.update.prompt.canceled");
            pause();
            return;
        }
        if (!newName.empty()) (*buildingIt)["building_name"] = newName;
        if (!newLocation.empty()) (*buildingIt)["building_location"] = newLocation;
        if (!newDormCountStr.empty()) (*buildingIt)["dormitories_count"] = newDormCountStr; // 新增
        if (!newBedCountStr.empty()) (*buildingIt)["bed_count"] = newBedCountStr;           // 新增
        nlohmann::json accRootData = Accommodations::readFromJson();
        accRootData["dormitory_building"] = allBuildings;
        if (Accommodations::writeInFile(accRootData)) {
            showSuccess(Text("admin.dorm.success.building_updated").getContent());
        } else {
            showError(Text("admin.dorm.error.write_failed").getContent());
        }

    } catch (const std::exception& e) {
        Text errorTip("admin.dorm.error.update_failed");
        showError(errorTip.getContent() + e.what());
    }

    pause();
}
void AdminDormitoryManagement::updateDormitory() {
    clearScreen();
    showTitle("admin.dorm.update.dorm.title");

    try {
        showPrompt("admin.dorm.update.prompt.view_before_update");
        pause();
        showDormCurrentInfo();

        clearScreen();
        std::string targetBuildingNum = getDigitInput(
            "admin.dorm.update.dorm.prompt.input_building_num_update",
            1, 3
        );
        std::string targetRoomNum = getDigitInput(
            "admin.dorm.update.dorm.prompt.input_room_num_update",
            3, 4
        );

        nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
        auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
            [&](const nlohmann::json& b) { return b["building_number"] == targetBuildingNum; });

        if (buildingIt == allBuildings.end()) {
            showError(Text("admin.dorm.error.building_not_found").getContent());
            pause();
            return;
        }

        nlohmann::json& dormList = (*buildingIt)["dormitories"];
        auto dormIt = std::find_if(dormList.begin(), dormList.end(),
            [&](const nlohmann::json& d) { return d["room_number"] == targetRoomNum; });

        if (dormIt == dormList.end()) {
            showError(Text("admin.dorm.error.dorm_not_found").getContent());
            pause();
            return;
        }

        std::string newTotalBedStr = getDigitInput("admin.dorm.update.dorm.prompt.input_new_total_bed", 1, 8);
        int maxVacant = newTotalBedStr.empty() ? (*dormIt)["total_bed"].get<int>() : std::stoi(newTotalBedStr);
        std::string newVacantBedStr = getDigitInput("admin.dorm.update.dorm.prompt.input_new_vacant_bed", 0, maxVacant);

        bool hasChange = false;
        if (!newTotalBedStr.empty()) hasChange = true;
        if (!newVacantBedStr.empty()) hasChange = true;
        if (!hasChange) {
            showPrompt("admin.dorm.update.prompt.no_change");
            pause();
            return;
        }

        if (!confirmOperation("admin.dorm.update.prompt.confirm")) {
            showPrompt("admin.dorm.update.prompt.canceled");
            pause();
            return;
        }

        if (!newTotalBedStr.empty()) (*dormIt)["total_bed"] = std::stoi(newTotalBedStr);
        if (!newVacantBedStr.empty()) (*dormIt)["vacant_bed"] = std::stoi(newVacantBedStr);

        nlohmann::json accRootData = Accommodations::readFromJson();
        accRootData["dormitory_building"] = allBuildings;
        if (Accommodations::writeInFile(accRootData)) {
            showSuccess(Text("admin.dorm.success.dorm_updated").getContent());
        } else {
            showError(Text("admin.dorm.error.write_failed").getContent());
        }

    } catch (const std::exception& e) {
        Text errorTip("admin.dorm.error.update_failed");
        showError(errorTip.getContent() + e.what());
    }

    pause();
}