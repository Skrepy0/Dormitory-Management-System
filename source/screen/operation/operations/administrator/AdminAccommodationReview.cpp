#include "../../../../../header/screen/operation/operations/administrator/AdminAccommodationReview.h"
#include "../../../../../header/data/Accommodations.h"
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stdexcept>    // 用于std::runtime_error

void AdminAccommodationReview::inputReviewApplications() {
    clearScreen();
    showTitle("operation.administrator.admin.accommodation.review.title");
    std::cout << std::endl;
    try {
        std::vector<json> pendingApps = loadPendingApplications();
        if (pendingApps.empty()) {
            showPrompt("operation.administrator.admin.accommodation.review.prompt.no_pending");
            std::cout << std::endl;
            pause();
            return;
        }


        json selectedApp = selectPendingApplication(pendingApps);
        if (selectedApp.empty()) {
            pause();
            return;
        }

        showApplicationDetail(selectedApp);

        bool isApproved = confirmOperation("operation.administrator.admin.accommodation.review.prompt.choose_result");
        std::string status = isApproved ? "approved" : "rejected";

        if (isApproved) {
            handleApprovedApplication(selectedApp);
            showSuccess("operation.administrator.admin.accommodation.review.success.approved");
        } else {
            showSuccess("operation.administrator.admin.accommodation.review.success.rejected");
        }

        selectedApp["status"] = status;

    } catch (const std::exception &e) {
        showError("operation.administrator.common.error.review_failed");
    }

    pause();
}

std::vector<json> AdminAccommodationReview::loadPendingApplications() {
    std::vector<json> pendingApps;
    try {
        nlohmann::json allStayData = StayLog::readJson();

        StayLog stayLog(allStayData);

        nlohmann::json checkInRecords = stayLog.getCheckInRecords();
        nlohmann::json checkOutRecords = stayLog.getCheckOutRecords();

        for (const auto& record : checkInRecords) {
            if (record.contains("status") && record["status"] == "pending") {
                pendingApps.push_back(record);
            }
        }

        for (const auto& record : checkOutRecords) {
            if (record.contains("status") && record["status"] == "pending") {
                pendingApps.push_back(record);
            }
        }
    } catch (const std::exception& e) {
        showError("operation.administrator.admin.accommodation.error.load_stay log_failed");
    }
    return pendingApps;
}
json AdminAccommodationReview::selectPendingApplication(const std::vector<json> &pendingApps) {
    showPrompt("operation.administrator.admin.accommodation.review.prompt.select_app");
    // 列出待审核申请
    for (size_t i = 0; i < pendingApps.size(); ++i) {
        const auto &app = pendingApps[i];
        std::cout << (i + 1) << ". "
                << "申请ID：" << app["apply_id"] << " | "
                << "类型：" << app["type"] << " | "
                << "申请人：" << app["user_name"] << std::endl;
    }

    std::string idxStr = getDigitInput(
            "operation.administrator.admin.accommodation.review.prompt.input_idx",
            1, static_cast<int>(pendingApps.size())
            );
    int idx = std::stoi(idxStr) - 1;
    return pendingApps[idx];
}

void AdminAccommodationReview::showApplicationDetail(const json &app) {
    clearScreen();
    showTitle("operation.administrator.admin.accommodation.review.title.detail");
    std::cout << Text("operation.administrator.admin.accommodation.review.label.app_id").getContent() << app["apply_id"]
            << std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.type").getContent() << app["type"] <<
            std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.user_id").getContent() << app["user_id"]
            << std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.user_name").getContent() << app[
        "user_name"] << std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.apply_time").getContent() << app[
        "apply_time"].dump(2) << std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.dorm_info").getContent() << app[
        "dorm_info"].dump(2) << std::endl;
    std::cout << Text("operation.administrator.admin.accommodation.review.label.reason").getContent() << app["reason"]
            << std::endl;
}

void AdminAccommodationReview::handleApprovedApplication(const json &app) {
    Time reviewTime = Time::getCurrentTime();

    Text typeText(app["type"] == "check-in" ? "user.accommodation.type.checkin" : "user.accommodation.type.checkout");
    StayLog reviewLog(
            typeText.getContent(),
            reviewTime,
            app["user_id"],
            app["user_name"],
            app["dorm_info"]
            );

    json reviewRecord = {
            {"apply_id", app["apply_id"]},
            {"review_time", reviewTime.getTime()},
            {"handler", "管理员"},
            {"status", "approved"}
    };

    if (app["type"] == "check-in") {
        reviewLog.addCheckInRecords(reviewRecord);
        updateDormVacantBed(app["dorm_info"], true); // 入宿：减少空闲床位
    } else {
        reviewLog.addCheckOutRecords(reviewRecord);
        updateDormVacantBed(app["dorm_info"], false); // 退宿：增加空闲床位
    }

    if (!reviewLog.writeToFile()) {
        throw std::runtime_error("写入StayLog失败");
    }
}

void AdminAccommodationReview::updateDormVacantBed(const json &dormInfo, bool isCheckIn) {
    std::string buildingNum = dormInfo["building_number"];
    std::string targetRoomNum = dormInfo["room_number"];

    long long buildingIdx = Accommodations::findBuildingByNumber(buildingNum);
    if (buildingIdx == -1) {
        throw std::runtime_error(
                Text("operation.administrator.admin.accommodation.error.building_not_found").getContent());
    }

    Accommodations acc;
    json buildingJson = acc.getBuildingJson(static_cast<int>(buildingIdx));
    BuildingData building(buildingJson);

    json dormList = building.getDormitoriesJson();
    if (dormList.empty()) {
        throw std::runtime_error(
                Text("operation.administrator.admin.accommodation.error.no_dorm_in_building").getContent());
    }

    bool roomFound = false;
    int totalBedPerDorm = std::stoi(building.getBedCount());
    for (auto &dorm: dormList) {
        if (dorm["room_number"] == targetRoomNum) {
            int currentVacant = dorm["vacant_bed"].get<int>();
            int newVacant = currentVacant;

            if (isCheckIn) {
                newVacant = std::max(0, currentVacant - 1);
            } else {
                newVacant = std::min(totalBedPerDorm, currentVacant + 1);
            }

            dorm["vacant_bed"] = newVacant;
            roomFound = true;
            break;
        }
    }

    if (!roomFound) {
        throw std::runtime_error(Text("operation.administrator.admin.accommodation.error.room_not_found").getContent());
    }

    if (!building.setDormitories(dormList)) {
        throw std::runtime_error(
                Text("operation.administrator.admin.accommodation.error.update_dorm_failed").getContent());
    }

    acc.eraseBuilding(buildingIdx);
    acc.addBuildings(building);

    if (!acc.writeInFile()) {
        throw std::runtime_error(
                Text("operation.administrator.admin.accommodation.error.write_dorm_failed").getContent());
    }
}
