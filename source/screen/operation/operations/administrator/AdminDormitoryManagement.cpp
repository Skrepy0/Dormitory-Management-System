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
    std::string name = getInput("operation.administrator.dorm.manage.prompt.building_name", true);
    std::string location = getInput("operation.administrator.dorm.manage.prompt.building_location", true);
    std::string number = getInput("operation.administrator.dorm.manage.prompt.building_number", true);
    std::string dormCount = getInput("operation.administrator.dorm.manage.prompt.dorm_count", true);
    std::string bedCount = getInput("operation.administrator.dorm.manage.prompt.bed_count", true);

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
    std::string buildingNumber = getInput("operation.administrator.dorm.manage.prompt.select_building");
    auto &acc = getAccommodations();
    long long buildingIndex = Accommodations::findBuildingByNumber(buildingNumber);

    if (buildingIndex == -1) {
        showError("operation.administrator.dorm.manage.error.building_not_found");
        pause();
        return;
    }

    nlohmann::json buildingJson = acc.getBuildingJson(static_cast<int>(buildingIndex));
    BuildingData targetBuilding(buildingJson);

    std::string roomNum = getInput("operation.administrator.dorm.manage.prompt.room_number");
    std::string floor = getInput("operation.administrator.dorm.manage.prompt.floor");
    std::string vacantBed = getInput("operation.administrator.dorm.manage.prompt.vacant_bed");

    for (auto i: buildingJson["dormitories"]) {
        if (roomNum == i["room_number"]) {
            showError("operation.administrator.dorm.manage.error.room_number_exists");
            pause();
            return;
        }
    }

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

    std::string buildingNumber = getInput("operation.administrator.dorm.manage.prompt.select_building");
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
    std::string buildingNumber = getInput("operation.administrator.dorm.manage.prompt.select_building");
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


    std::string roomNum = getInput("operation.administrator.dorm.manage.prompt.select_dorm");
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
    std::string targetBuildingNum = getDigitInput("admin.dorm.update.building.prompt.input_building_num", 1, 3);
    nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
    auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
                                   [&](const nlohmann::json &b) { return b["building_number"] == targetBuildingNum; });

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
    std::string targetBuildingNum = getDigitInput("admin.dorm.update.dorm.prompt.input_building_num", 1, 3);
    nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
    auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(),
                                   [&](const nlohmann::json &b) { return b["building_number"] == targetBuildingNum; });

    if (buildingIt == allBuildings.end()) {
        showError(Text("admin.dorm.error.building_not_found").getContent());
        pause();
        return;
    }
    std::string targetRoomNum = getDigitInput("admin.dorm.update.dorm.prompt.input_room_num", 3, 4);
    nlohmann::json &dormList = (*buildingIt)["dormitories"];
    auto dormIt = std::find_if(dormList.begin(), dormList.end(),
                               [&](const nlohmann::json &d) { return d["room_number"] == targetRoomNum; });

    if (dormIt == dormList.end()) {
        showError(Text("admin.dorm.error.dorm_not_found").getContent());
        pause();
        return;
    }
    nlohmann::json maintenances = (*dormIt)["maintenances"];
    nlohmann::json latestMaintenance;
    bool hasMaintenance = false;

    if (!maintenances.empty()) {
        std::sort(maintenances.begin(), maintenances.end(), [](const nlohmann::json &a, const nlohmann::json &b) {
            const auto &aTime = a["report_time"];
            const auto &bTime = b["report_time"];
            if (aTime["year"] != bTime["year"])
                return aTime["year"] > bTime["year"];
            if (aTime["month"] != bTime["month"])
                return aTime["month"] > bTime["month"];
            if (aTime["day"] != bTime["day"])
                return aTime["day"] > bTime["day"];
            if (aTime["hour"] != bTime["hour"])
                return aTime["hour"] > bTime["hour"];
            if (aTime["minute"] != bTime["minute"])
                return aTime["minute"] > bTime["minute"];
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
    showContent((*dormIt)["bed_count"]);
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
        std::string targetBuildingNum =
                getDigitInput("admin.dorm.update.building.prompt.input_building_num_update", 1, 3);
        nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
        auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(), [&](const nlohmann::json &b) {
            return b["building_number"] == targetBuildingNum;
        });

        if (buildingIt == allBuildings.end()) {
            showError(Text("admin.dorm.error.building_not_found").getContent());
            pause();
            return;
        }
        std::string newName = getInput("admin.dorm.update.building.prompt.input_new_name", true);

        std::string newLocation = getInput("admin.dorm.update.building.prompt.input_new_location", true);

        std::string newDormCountStr = getDigitInput("admin.dorm.update.building.prompt.input_new_dorm_count", 0, 999);

        std::string newBedCountStr = getDigitInput("admin.dorm.update.building.prompt.input_new_bed_count", 0, 8);
        bool hasChange = false;
        if (!newName.empty())
            hasChange = true;
        if (!newLocation.empty())
            hasChange = true;
        if (!newDormCountStr.empty())
            hasChange = true;
        if (!newBedCountStr.empty())
            hasChange = true;

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
        if (!newName.empty())
            (*buildingIt)["building_name"] = newName;
        if (!newLocation.empty())
            (*buildingIt)["building_location"] = newLocation;
        if (!newDormCountStr.empty())
            (*buildingIt)["dormitories_count"] = newDormCountStr; // 新增
        if (!newBedCountStr.empty())
            (*buildingIt)["bed_count"] = newBedCountStr; // 新增
        nlohmann::json accRootData = Accommodations::readFromJson();
        accRootData["dormitory_building"] = allBuildings;
        if (Accommodations::writeInFile(accRootData)) {
            showSuccess(Text("admin.dorm.success.building_updated").getContent());
        } else {
            showError(Text("admin.dorm.error.write_failed").getContent());
        }

    } catch (const std::exception &e) {
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
        std::string targetBuildingNum = getDigitInput("admin.dorm.update.dorm.prompt.input_building_num_update", 0, 3);
        std::string targetRoomNum = getDigitInput("admin.dorm.update.dorm.prompt.input_room_num_update", 0, 4);

        nlohmann::json allBuildings = DataHelper::getDormitoryBuildingList();
        auto buildingIt = std::find_if(allBuildings.begin(), allBuildings.end(), [&](const nlohmann::json &b) {
            return b["building_number"] == targetBuildingNum;
        });

        if (buildingIt == allBuildings.end()) {
            showError(Text("admin.dorm.error.building_not_found").getContent());
            pause();
            return;
        }

        nlohmann::json &dormList = (*buildingIt)["dormitories"];
        auto dormIt = std::find_if(dormList.begin(), dormList.end(),
                                   [&](const nlohmann::json &d) { return d["room_number"] == targetRoomNum; });

        if (dormIt == dormList.end()) {
            showError(Text("admin.dorm.error.dorm_not_found").getContent());
            pause();
            return;
        }
        std::string value = getDigitInput("admin.dorm.update.dorm.prompt.input_new_total_bed", 0, 8);
        std::string newTotalBedStr = value.empty() ? static_cast<std::string>((*dormIt)["bed_count"]) : value;
        int maxVacant = newTotalBedStr.empty() ? (*dormIt)["bed_count"].get<int>() : std::stoi(newTotalBedStr);
        value = getDigitInput("admin.dorm.update.dorm.prompt.input_new_vacant_bed", 0, maxVacant);
        std::string newVacantBedStr = value.empty() ? nlohmann::to_string((*dormIt)["vacant_bed"]) : value;
        bool hasChange = false;
        if (!newTotalBedStr.empty())
            hasChange = true;
        if (!newVacantBedStr.empty())
            hasChange = true;
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

        if (!newTotalBedStr.empty())
            (*dormIt)["bed_count"] = newTotalBedStr;
        if (!newVacantBedStr.empty())
            (*dormIt)["vacant_bed"] = std::stoi(newVacantBedStr);

        nlohmann::json accRootData = Accommodations::readFromJson();
        accRootData["dormitory_building"] = allBuildings;
        if (Accommodations::writeInFile(accRootData)) {
            showSuccess(Text("admin.dorm.success.dorm_updated").getContent());
        } else {
            showError(Text("admin.dorm.error.write_failed").getContent());
        }

    } catch (const std::exception &e) {
        Text errorTip("admin.dorm.error.update_failed");
        showError(errorTip.getContent() + e.what());
    }

    pause();
}
void AdminDormitoryManagement::showStudentCheckInRecord() {
    clearScreen();
    showTitle("admin.dorm.review.title.student_checkin_record");
    std::cout << std::endl;
    try {
        std::string studentId = getInput("admin.dorm.prompt.input_student_id");
        nlohmann::json checkInRecords = StayLog::getCheckInRecords();
        std::vector<nlohmann::json> studentCheckInRecords;

        for (const auto &record: checkInRecords) {
            if (record["apply_id"].get<std::string>() == studentId) {
                studentCheckInRecords.push_back(record);
            }
        }

        if (studentCheckInRecords.empty()) {
            showPrompt("admin.dorm.prompt.no_student_checkin_record");
            pause();
            return;
        }

        showTitle("admin.dorm.review.title.student_checkin_list");
        std::cout << std::endl;
        for (size_t i = 0; i < studentCheckInRecords.size(); ++i) {
            const auto &record = studentCheckInRecords[i];
        }

        for (const auto &record: studentCheckInRecords) {
            showContent("admin.dorm.label.apply_id");
            std::cout << record["apply_id"].get<std::string>() << std::endl;

            showContent("admin.dorm.label.student_name");
            std::cout << record["initiator"].get<std::string>() << std::endl;
            showContent("admin.dorm.label.operate_time");
            if (record.contains("apply_time") && !record["apply_time"].is_null()) {
                const nlohmann::json &applyTime = record["apply_time"];
                showContent("admin.dorm.label.operate_time.year");
                showContent(std::to_string(applyTime["year"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.month");
                showContent(std::to_string(applyTime["month"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.day");
                showContent(std::to_string(applyTime["day"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.hour");
                showContent(std::to_string(applyTime["hour"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.minute");
                showContent(std::to_string(applyTime["minute"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.second");
                showContent(std::to_string(applyTime["second"].get<int>()));
                std::cout << std::endl;
            }
            if (record.contains("dormitory")) {
                const nlohmann::json &dorm = record["dormitory"];
                showContent("admin.dorm.label.building_name");
                showContent(dorm["building_name"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.building_num");
                showContent(dorm["building_number"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.room_num");
                showContent(dorm["room_number"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.bed_count");
                showContent(dorm["bed_number"].get<std::string>());
                std::cout << std::endl;
            }
            showContent("admin.dorm.label.status");
            showContent(record["status"].get<std::string>());
            std::cout << std::endl;
            showContent("----------------------------------------\n");
        }

    } catch (const std::exception &e) {
        showError("admin.dorm.error.load_record");
    }

    pause();
}
void AdminDormitoryManagement::showStudentCheckOutRecord() {
    clearScreen();
    showTitle("admin.dorm.review.title.student_checkout_record");
    std::cout << std::endl;
    try {
        std::string studentId = getInput("admin.dorm.prompt.input_student_id");
        std::cout << std::endl;
        nlohmann::json checkOutRecords = StayLog::getCheckOutRecords();
        std::vector<nlohmann::json> studentCheckOutRecords;

        for (const auto &record: checkOutRecords) {
            if (record["apply_id"].get<std::string>() == studentId) {
                studentCheckOutRecords.push_back(record);
            }
        }


        if (studentCheckOutRecords.empty()) {
            showPrompt("admin.dorm.prompt.no_student_checkout_record");
            pause();
            return;
        }


        showTitle("admin.dorm.review.title.student_checkout_list");
        std::cout << std::endl;
        for (size_t i = 0; i < studentCheckOutRecords.size(); ++i) {
            const auto &record = studentCheckOutRecords[i];
        }

        for (const auto &record: studentCheckOutRecords) {
            showContent("admin.dorm.label.apply_id");
            std::cout << record["apply_id"].get<std::string>() << std::endl;

            showContent("admin.dorm.label.student_name");
            std::cout << record["initiator"].get<std::string>() << std::endl;
            showContent("admin.dorm.label.operate_time");
            if (record.contains("apply_time") && !record["apply_time"].is_null()) {
                const nlohmann::json &applyTime = record["apply_time"];
                showContent("admin.dorm.label.operate_time.year");
                showContent(std::to_string(applyTime["year"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.month");
                showContent(std::to_string(applyTime["month"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.day");
                showContent(std::to_string(applyTime["day"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.hour");
                showContent(std::to_string(applyTime["hour"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.minute");
                showContent(std::to_string(applyTime["minute"].get<int>()));
                std::cout << std::endl;
                showContent("admin.dorm.label.operate_time.second");
                showContent(std::to_string(applyTime["second"].get<int>()));
                std::cout << std::endl;
            }

            if (record.contains("dormitory")) {
                const nlohmann::json &dorm = record["dormitory"];
                showContent("admin.dorm.label.building_name");
                showContent(dorm["building_name"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.building_num");
                showContent(dorm["building_number"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.room_num");
                showContent(dorm["room_number"].get<std::string>());
                std::cout << std::endl;
                showContent("admin.dorm.label.bed_count");
                showContent(dorm["bed_number"].get<std::string>());
                std::cout << std::endl;
            }

            showContent("admin.dorm.label.status");
            showContent(record["status"].get<std::string>());
            std::cout << std::endl;
            showContent("----------------------------------------\n");
        }

    } catch (const std::exception &e) {
        showError("admin.dorm.error.load_record");
    }

    pause();
}
