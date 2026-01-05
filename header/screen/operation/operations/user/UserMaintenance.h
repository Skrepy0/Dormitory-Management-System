#pragma once
#include "../../../../data/basic/Time.h"
#include "../../../InputMenu.h"
class UserMaintenance : public InputMenu {
private:
    Time reportTime; // 自动记录的报修时间
    Time repairTime; // 维修时间（初始为空）
    std::string sponsor; // 报修人（用户输入）
    std::string description; // 报修描述（用户输入）
    std::string repairer; // 维修者（初始为空）
    bool state; // 报修状态（默认false=未处理）
    std::string valuation; // 报修评价（初始为空）
public:
    std::string getCurrentTime();
    void submitRepair();
};
