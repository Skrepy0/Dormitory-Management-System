#ifndef ADMINACCOMMODATIONREVIEW_H
#define ADMINACCOMMODATIONREVIEW_H

#include <string>
#include <vector>
#include "../../../../data/StayLog.h"
#include "../../../InputMenu.h"
#include "Time.h"

using json = nlohmann::json;class AdminAccommodationReview : public InputMenu {
public:
    // 审核申请主流程（入口）
    void inputReviewApplications();

private:
    // 加载待审核的申请（筛选time为null/未处理的记录）
    std::vector<json> loadPendingApplications();

    // 让管理员选择待审核的申请
    json selectPendingApplication(const std::vector<json>& pendingApps, const std::string& type);

    // 显示申请详情
    void showApplicationDetail(const json& app, const std::string& type);

    // 处理通过的申请（更新审核人、时间，写回记录）
    void handleApprovedApplication(json& app, const std::string& type, const std::string& adminName);

    // 更新宿舍空闲床位（入住减1/退宿加1）
    void updateDormVacantBed(const json& dormInfo, bool isCheckIn);
};
#endif // ADMINACCOMMODATIONREVIEW_H
