#pragma once
#include "../../../../../header/data/HashHelper.h"
#include "../../../../../header/data/StayLog.h"
#include "../../../InputMenu.h"
using json = nlohmann::json;

class UserApplication : public InputMenu {
public:
    static void inputCheckInApplication();

    // 退宿申请主流程
    static void inputCheckOutApplication();


    static std::string getDormApplyReason(); // 获取申请理由（退宿/调宿）
private:
    // 辅助：收集宿舍信息（入/退宿通用）
    static json collectDormInfo(const std::string &applyTypeKey);

    // 辅助：生成申请唯一标识（适配Time类）
    std::string generateApplyId(const std::string &userId);
};
