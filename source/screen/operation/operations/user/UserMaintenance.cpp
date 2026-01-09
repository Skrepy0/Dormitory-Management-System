#include "../../../../../header/screen/operation/operations/user/UserMaintenance.h"
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include <windows.h>

#include "../../../../../header/data/Accommodations.h"
#include "../../../../../header/data/DataHelper.h"
#include "../../../../../header/data/HashHelper.h"
#include "../../../../../header/data/UserData.h"
#include "../../../../../header/data/basic/Maintenance.h"
#include "../../../../../header/data/basic/Time.h"
void init() {}
void UserMaintenance::upLoadNewMaintenance() {
    Maintenance maintenance(reportTime, repairTime, sponsor, description, repairer, false, "",
                            HashHelper::getHashFromCurrentTime());
    std::string id = DataHelper::readTempFromJson()["id"];
    nlohmann::json userData = DataHelper::getUser(id);
    long long buildingIndex =
            Accommodations::findBuildingByNumber(DataHelper::getDormitory(userData)["building_number"]);
    nlohmann::json buildingData = DataHelper::getDormitoryBuildingList()[buildingIndex];
    for (auto &room: buildingData["dormitories"]) {
        if (room["room_number"] == userData["dormitory"]["room_number"]) {
            room["maintenances"].push_back(maintenance.getMaintenanceData());
            break;
        }
    }
    Accommodations newAccommodations;
    newAccommodations.eraseBuilding(buildingIndex);
    newAccommodations.addBuildings(BuildingData(buildingData));
    newAccommodations.writeInFile();
}

std::string UserMaintenance::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&currentTime);

    char timeBuf[64];
    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &localTime);
    return std::string(timeBuf);
}

void UserMaintenance::submitRepair() {

    showTitle("screen.operation.operations.UserMaintenance.title");
    std::cout << std::endl;


    sponsor = getInput("screen.operation.operations.UserMaintenance.sponsor");
    description = getInput("screen.operation.operations.UserMaintenance.repair.content");
    bool isConfirm = confirmOperation("screen.operation.operations.UserMaintenance.repair.confirmation");
    if (isConfirm) {
        showSuccess("screen.operation.operations.UserMaintenance.repair.success");
        pause();
    } else {
        showError("screen.operation.operations.UserMaintenance.repair.error");
        pause();
    }

    std::string currentTimeStr = getCurrentTime();
    int year, month, day, hour, minute, second;

    if (sscanf(currentTimeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        showError("screen.operation.operations.UserMaintenance.time_format.error");
        pause();
        return;
    }
    try {
        reportTime = Time(year, month, day, hour, minute, second);
    } catch (const std::invalid_argument &e) {
        showError("screen.operation.operations.UserMaintenance.repair_time.error");
        pause();
        return;

        try {
            repairTime = Time(2000, 1, 1, 0, 0, 0); // 初始化为合法默认值（后续由管理员修改）
        } catch (const std::invalid_argument &e) {
            showError("screen.operation.operations.UserMaintenance.repair_time.error");
            pause();
            return;
        }

        repairer = "";
        state = false;
        valuation = "";
    }
    upLoadNewMaintenance();
}
void UserMaintenance::submitValuation() {
    showTitle("screen.operation.operations.UserMaintenance.valuation.title"); // 对应JSON键
    std::cout << std::endl;
    if (!state) {
        showError("screen.operation.operations.UserMaintenance.valuation.invalid.state");
        pause();
        return;
    }

    if (!valuation.empty()) {
        showError("screen.operation.operations.UserMaintenance.valuation.already.submitted");
        pause();
        return;
    }

    std::string evalContent = getInput("screen.operation.operations.UserMaintenance.valuation.prompt");

    bool isConfirm = confirmOperation("screen.operation.operations.UserMaintenance.valuation.confirm");

    if (isConfirm) {

        valuation = evalContent;
        upLoadNewMaintenance();
        showSuccess("screen.operation.operations.UserMaintenance.valuation.success");
    } else {
        showError("screen.operation.operations.UserMaintenance.valuation.cancel");
    }

    pause();
}
