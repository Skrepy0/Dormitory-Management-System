#ifndef ADMINACCOMMODATIONREVIEW_H
#define ADMINACCOMMODATIONREVIEW_H

#include "../../../InputMenu.h"
#include "../../../../data/StayLog.h"
#include "Time.h"
#include <vector>
#include <string>

using json = nlohmann::json;

// 管理员审核入/退宿申请类（继承InputMenu处理交互）
class AdminAccommodationReview : public InputMenu {
public:
    // 审核申请主流程
    void inputReviewApplications();

private:
    // 辅助：加载待审核的申请列表
    std::vector<json> loadPendingApplications();

    // 辅助：让管理员选择待审核的申请
    json selectPendingApplication(const std::vector<json>& pendingApps);

    // 辅助：显示申请详情
    void showApplicationDetail(const json& app);

    // 辅助：处理“审核通过”的申请（更新房间状态+写入StayLog）
    void handleApprovedApplication(const json& app);

    // 辅助：更新宿舍房间的空闲床位状态
    void updateDormVacantBed(const json& dormInfo, bool isCheckIn);
};

#endif // ADMINACCOMMODATIONREVIEW_H