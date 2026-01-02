#pragma once
#include "../../InputMenu.h"
class UserApplication : public InputMenu
{
public:
    std::string getDormApplyReason(); // 获取申请理由（退宿/调宿）
    std::string getRepairContentInput(); // 获取报修内容
    void getRepairAndApplyInfo(); // 串联报修内容+申请理由的输入
};

//这个类中包含宿舍申请和报修申请
