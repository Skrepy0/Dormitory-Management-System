//
// Created by Skrepy on 2026/1/10.
//

#include "../../../../../header/screen/operation/operations/administrator/AdminMaintenanceReview.h"

#include "../../../../../header/data/DataHelper.h"
#include "../../../../../header/data/info/Message.h"
#include "../../../../../header/screen/operation/operations/administrator/AdminAccommodationReview.h"

void AdminMaintenanceReview::show() {
    clearScreen();
    showTitle("admin.maintenances.review.title");
    nlohmann::json buildingList = DataHelper::getDormitoryBuildingList();
    std::vector<nlohmann::json> pendingMaintenance;
    for (nlohmann::json &building: buildingList) {
        for (nlohmann::json &room: building["dormitories"]) {
            for (nlohmann::json &maintenance: room["maintenances"]) {
                if (!maintenance["state"].get<bool>()) {
                    pendingMaintenance.push_back(maintenance);
                }
            }
        }
    }
    // 无待审核申请
    if (pendingMaintenance.empty()) {
        showPrompt("admin.maintenances.review.prompt.no_pending");
        pause();
        return;
    }
    clearScreen();
    showTitle("admin.maintenances.review.title");
    int index = 0;
    for (const auto &i: pendingMaintenance) {
        index++;
        Message(Text::of("$l"+ std::to_string(index)+".$r\n")).printContent();
        showContent("admin.maintenances.label.report_time");
        const json &time = i["report_time"];
        std::string reportTime =
                std::to_string(time["year"].get<int>()) + "年" + std::to_string(time["month"].get<int>()) + "月" +
                std::to_string(time["day"].get<int>()) + "日 " + std::to_string(time["hour"].get<int>()) + ":" +
                std::to_string(time["minute"].get<int>()) + ":" + std::to_string(time["second"].get<int>());
        showContent(reportTime);
        showContent("\n");

        showContent("admin.maintenances.label.sponsor");
        showContent(i["sponsor"]);
        showContent("\n");

        showContent("admin.maintenances.label.description");
        showContent(i["description"]);
        showContent("\n");

        showContent("admin.maintenances.label.id");
        showContent(i["id"]);
        showContent("\n");

        Message(Text::of("$s------------------------------------------------------------------\n$r")).printContent();
    }
    int choice = stoi(getInput("admin.maintenances.label.choice"));
}
