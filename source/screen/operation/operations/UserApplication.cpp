#include "../../../../header/screen/operation/operations/UserApplication.h"
#include"../../../../header/data/info/Message.h"
#include"../../../../header/data/info/Text.h"
// 获取申请理由（非空+长度限制）
std::string UserApplication::getDormApplyReason()
{
    std::string reason;
    while (true)
    {
        reason = getNonEmptyInput("screen.operation.operations.UserApplication.DormApplyReason.Input");
        if (reason.length() <= 50) return reason;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.error");
    }
}
// 获取报修内容
std::string UserApplication::getRepairContentInput()
{
    return getNonEmptyInput("screen.operation.operations.UserApplication.getRepairContentInput");
}

void UserApplication::getRepairAndApplyInfo()
{
    std::string repairContent = getRepairContentInput();
    std::string applyReason = getDormApplyReason();
    Text t("screen.operation.operations.UserApplication.getRepairAndApplyInfo.repair_content");
    Text t1("screen.operation.operations.UserApplication.getRepairAndApplyInfo.application_reason");
    std::cout << t.getContent()<< repairContent << std::endl;
    std::cout << t1.getContent() << applyReason << std::endl;
}
