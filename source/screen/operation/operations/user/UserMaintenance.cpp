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
#include "../../../../../header/data/info/Message.h"
#include "../../../../../header/screen/operation/operations/administrator/AdminAccommodationReview.h"
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
    nlohmann::json buildingList = DataHelper::getDormitoryBuildingList();
    std::vector<nlohmann::json> approvedMaintenance;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, json>>> maintenanceMap;
    for (int i = 0; i < buildingList.size(); i++) {
        nlohmann::json building = buildingList[i];
        for (int j = 0; j < building["dormitories"].size(); j++) {
            nlohmann::json room = building["dormitories"][j];
            for (int k = 0; k < room["maintenances"].size(); k++) {
                nlohmann::json maintenance = room["maintenances"][k];
                if (maintenance["state"].get<bool>() &&
                    maintenance["valuation"].get<std::string>().empty()) {
                    approvedMaintenance.push_back(maintenance);
                    maintenanceMap.push_back({{i, j}, {k,maintenance["report_time"]}});
                }
            }
        }
    }

    std::sort(maintenanceMap.begin(), maintenanceMap.end(), [](std::pair<std::pair<int, int>, std::pair<int, json>> &a, std::pair<std::pair<int, int>, std::pair<int, json>> &b) {
                const auto &aTime = a.second.second;
                const auto &bTime = b.second.second;
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
    if (approvedMaintenance.empty()) {
        showError("screen.operation.operations.UserMaintenance.valuation.already.submitted");
        pause();
        return;
    }
    state = approvedMaintenance[0]["state"].get<bool>();
    if (!state) {
        showError("screen.operation.operations.UserMaintenance.valuation.invalid.state");
        pause();
        return;
    }

    json dor = approvedMaintenance[0];
    showContent("admin.maintenances.label.report_time");
    const json &time = dor["report_time"];
    std::string reportTime =
            std::to_string(time["year"].get<int>()) + "年" + std::to_string(time["month"].get<int>()) + "月" +
            std::to_string(time["day"].get<int>()) + "日 " + std::to_string(time["hour"].get<int>()) + ":" +
            std::to_string(time["minute"].get<int>()) + ":" + std::to_string(time["second"].get<int>());
    showContent(reportTime);
    showContent("\n");

    showContent("admin.maintenances.label.sponsor");
    showContent(dor["sponsor"]);
    showContent("\n");

    showContent("admin.maintenances.label.description");
    showContent(dor["description"]);
    showContent("\n");

    showContent("admin.maintenances.label.id");
    showContent(dor["id"]);
    showContent("\n");

    Message(Text::of("$s------------------------------------------------------------------\n$r")).printContent();

    std::string evalContent = getInput("screen.operation.operations.UserMaintenance.valuation.prompt");

    bool isConfirm = confirmOperation("screen.operation.operations.UserMaintenance.valuation.confirm");

    if (isConfirm) {
        valuation = evalContent;
        auto maintenance = approvedMaintenance[0];
        maintenance["valuation"] = valuation;
        json &maintenanceList = buildingList[maintenanceMap[0].first.first]["dormitories"]
                                        [maintenanceMap[0].first.second]["maintenances"];
        maintenanceList.erase(maintenanceList.begin() + maintenanceMap[0].second.first);
        maintenanceList.push_back(maintenance);
        Accommodations acc;
        acc.eraseBuilding(maintenanceMap[0].first.first);
        acc.addBuildings(buildingList[maintenanceMap[0].first.first]);
        acc.writeInFile();
        showSuccess("screen.operation.operations.UserMaintenance.valuation.success");
    } else {
        showError("screen.operation.operations.UserMaintenance.valuation.cancel");
    }

    pause();
}
