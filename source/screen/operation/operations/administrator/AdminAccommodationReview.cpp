#include "../../../../../header/screen/operation/operations/administrator/AdminAccommodationReview.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <stdexcept> // 用于std::runtime_error
#include <string>
#include <vector>
#include "../../../../../header/data/Accommodations.h"
#include "../../../../../header/data/DataHelper.h"

// 主审核流程（仅用InputMenu交互+DataHelper函数）
void AdminAccommodationReview::inputReviewApplications() {
    clearScreen();
    showTitle("admin.accommodation.review.title");

    try {
        auto dataPair = loadPendingApplications();
        auto pendingCheckIn = dataPair.first;
        auto pendingCheckOut = dataPair.second;
        // 1. 加载「入住/退宿」待审核申请（用DataHelper关联的StayLog）

        // 无待审核申请
        if (pendingCheckIn.empty() && pendingCheckOut.empty()) {
            showPrompt("admin.accommodation.review.prompt.no_pending");
            pause();
            return;
        }

        // 2. 选择申请类型（替换getStringInput：用数字选项+getIntInput）
        showPrompt("admin.accommodation.review.prompt.select_type");
        showContent("1. 入住申请");
        showContent("2. 退宿申请");
        int typeChoice = std::stoi(getDigitInput("admin.accommodation.review.prompt.input_type_choice", 1, 2));
        std::string type = (typeChoice == 1) ? "check-in" : "check-out";
        json targetPending = (type == "check-in") ? pendingCheckIn : pendingCheckOut;

        if (targetPending.empty()) {
            showPrompt(type == "check-in" ? "admin.accommodation.review.prompt.no_pending_check-in"
                                          : "admin.accommodation.review.prompt.no_pending_check-out");
            pause();
            return;
        }

        // 3. 选择具体申请（用InputMenu的getIntInput选序号）
        json selectedApp = selectPendingApplication(targetPending, type);
        if (selectedApp.is_null()) {
            pause();
            return;
        }
        // 4. 显示申请详情
        showApplicationDetail(selectedApp, type);

        // 5. 确认审核结果（用InputMenu的confirmOperation）
        if (confirmOperation("admin.accommodation.review.prompt.confirm_approve")) {
            // 处理通过（管理员名称从会话获取，这里示例用"admin"）
            handleApprovedApplication(selectedApp, type, "admin");
            showSuccess("admin.accommodation.review.success.approved");
        } else {
            showPrompt("admin.accommodation.review.prompt.rejected");
        }

    } catch (const std::exception &e) {
        showError(Text("admin.accommodation.review.error").getContent() + e.what());
    }
    pause();
}

// 加载待审核申请（用DataHelper关联的StayLog，拆分入住/退宿列表）
std::pair<json, json> AdminAccommodationReview::loadPendingApplications() {
    return {DataHelper::getCheckInApplicationToBeReviewedList(), DataHelper::getCheckOutApplicationToBeReviewedList()};
}

// 选择待审核申请（用InputMenu的showContent展示+getIntInput选序号）
json AdminAccommodationReview::selectPendingApplication(const json &pendingApps, const std::string &type) {
    clearScreen();
    showTitle(type == "check-in" ? "admin.accommodation.review.title.select_check-in"
                                 : "admin.accommodation.review.title.select_check-out");

    // 展示申请列表（仅用InputMenu的showContent）
    int i = 0;
    for (auto app: pendingApps) {
        i++;
        showContent(std::to_string(i));
        showContent(". 申请ID: ");
        showContent(app["apply_id"]);
        showContent(" | 申请人: ");
        showContent(app["initiator"]);
        showContent("\n");
    }

    // 选择序号（用InputMenu的getIntInput）
    int choice = std::stoi(getDigitInput("admin.accommodation.review.prompt.input_choice", 1, pendingApps.size()));
    if (choice <= 0 || choice > pendingApps.size()) {
        showError("admin.accommodation.review.error.invalid_choice");
        return NULL;
    }
    return pendingApps[choice - 1];
}

// 显示申请详情（用DataHelper的getDormitory逻辑，仅InputMenu展示）
void AdminAccommodationReview::showApplicationDetail(const json &app, const std::string &type) {
    clearScreen();
    showTitle("admin.accommodation.review.title.detail");

    // 申请基础信息
    showContent("admin.accommodation.label.type");
    showContent(type == "check-in" ? "入住申请" : "退宿申请");
    showContent("admin.accommodation.label.apply_id");
    showContent(app["apply_id"]);
    std::cout << std::endl;
    showContent("admin.accommodation.label.applicant");
    showContent(app["initiator"]);
    std::cout << std::endl;
    showContent("admin.accommodation.label.reason");
    showContent(app["reason"]);
    std::cout << std::endl;
    // 申请时间（格式化）
    if (app.contains("apply_time")) {
        const json &time = app["apply_time"];
        std::string applyTime =
                std::to_string(time["year"].get<int>()) + "年" + std::to_string(time["month"].get<int>()) + "月" +
                std::to_string(time["day"].get<int>()) + "日 " + std::to_string(time["hour"].get<int>()) + ":" +
                std::to_string(time["minute"].get<int>()) + ":" + std::to_string(time["second"].get<int>());
        showContent("admin.accommodation.label.apply_time");
        showContent(applyTime);
    }

    // 宿舍信息（用DataHelper的getDormitory逻辑，直接取申请内的dormitory）
    if (app.contains("dormitory")) {
        const json &dorm = app["dormitory"];
        showContent("admin.accommodation.label.building");
        showContent(dorm["building_name"].get<std::string>() + "(" + dorm["building_number"].get<std::string>() + ")");
        std::cout << std::endl;
        showContent("admin.accommodation.label.room");
        showContent(dorm["room_number"].get<std::string>());
        std::cout << std::endl;
        showContent("admin.accommodation.label.bed");
        showContent(dorm["bed_number"].get<std::string>());
        std::cout << std::endl;
    }

    showContent("----------------------------------------");
    pause();
}

// 处理通过的申请（用DataHelper的findStayLogByHash定位记录）
void AdminAccommodationReview::handleApprovedApplication(json &app, const std::string &type,
                                                         const std::string &adminName) {
    // 1. 用DataHelper找申请对应的记录索引
    int recordIndex = DataHelper::findStayLogByHash(type, app["hash"].get<std::string>());
    if (recordIndex == -1) {
        throw std::runtime_error("申请记录不存在");
    }

    // 2. 更新记录的审核信息
    json allRecords = (type == "check-in") ? StayLog::getCheckInRecords() : StayLog::getCheckOutRecords();
    allRecords[recordIndex]["handler"] = adminName;
    Time currentTime = Time::getCurrentTime();
    allRecords[recordIndex]["time"] = currentTime.getTime();
    allRecords[recordIndex]["status"] = "approved";
    StayLog::delStayLog(recordIndex, type);
    StayLog::addCheckInRecords(allRecords[recordIndex]);

    // 4. 更新宿舍空闲床位（用DataHelper的getDormitoryBuildingList）
    updateDormVacantBed(app, type == "check-in");
}

// 更新宿舍空闲床位（用DataHelper的getDormitoryBuildingList）
void AdminAccommodationReview::updateDormVacantBed(const json &app, bool isCheckIn) {
    // 1. 用DataHelper获取宿舍楼列表
    json buildings = DataHelper::getDormitoryBuildingList();
    std::string buildingNum = app["dormitory"]["building_number"].get<std::string>();
    std::string roomNum = app["dormitory"]["room_number"].get<std::string>();
    if (!isCheckIn) {
        nlohmann::json user = DataHelper::getUser(app["apply_id"]);
        nlohmann::json dormitory = DataHelper::getDormitory(user);
        std::string buildingNumber = user["dormitory"]["building_number"];
        json building = DataHelper::getDormitoryBuildingList()[Accommodations::findBuildingByNumber(buildingNum)];
        dormitory["vacant_bed"] += 1;
        user["dormitory"]["bed_number"] = -1;
        user["dormitory"]["building_name"] = "";
        user["dormitory"]["building_number"] = "";
        user["dormitory"]["floor"] = "";
        user["dormitory"]["room_number"] = "";
        user["dormitory"]["vacant_bed"] = -1;
        UserData::eraseUserById(app["apply_id"]);
        UserData::addFromJson(user);
        int res = 0;
        for (int i = 0; i < building["dormitories"]; i++) {
            if (building["dormitories"][i]["room_number"] == roomNum) {
                res = i;
                break;
            }
        }
        building["dormitories"].erase(building["dormitories"].begin() + res);
        building["dormitories"].push_back(dormitory);
        Accommodations acc;
        acc.eraseBuilding(Accommodations::findBuildingByNumber(buildingNumber));
        acc.addBuildings(building);
    } else {
        nlohmann::json user = DataHelper::getUser(app["apply_id"]);
        std::string buildingNumber = user["dormitory"]["building_number"];
        json building = DataHelper::getDormitoryBuildingList()[Accommodations::findBuildingByNumber(buildingNumber)];
        json dormitory;
        for (int i = 0; i < building["dormitories"].size(); i++) {
            if (building["dormitories"][i]["room_number"] == roomNum) {
                dormitory = building["dormitories"][i];
                break;
            }
        }
        dormitory["vacant_bed"] = dormitory["vacant_bed"].get<int>() - 1;
        user["dormitory"]["bed_number"] = std::stoi(dormitory["bed_count"].get<std::string>());
        user["dormitory"]["building_name"] = dormitory["building_name"];
        user["dormitory"]["building_number"] = dormitory["building_number"];
        user["dormitory"]["floor"] = dormitory["floor"];
        user["dormitory"]["room_number"] = dormitory["room_number"];
        user["dormitory"]["vacant_bed"] = dormitory["vacant_bed"].get<int>();
        UserData::eraseUserById(app["apply_id"]);
        UserData::addFromJson(user);
        int res = 0;
        for (int i = 0; i < building["dormitories"]; i++) {
            if (building["dormitories"][i]["room_number"] == roomNum) {
                res = i;
                break;
            }
        }
        building["dormitories"].erase(building["dormitories"].begin() + res);
        building["dormitories"].push_back(dormitory);
        Accommodations acc;
        acc.eraseBuilding(Accommodations::findBuildingByNumber(buildingNumber));
        acc.addBuildings(building);
        acc.writeInFile();
    }
}
