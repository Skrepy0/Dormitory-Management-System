#include "../../../../header/screen/operation/operations/UserApplication.h"
#include"../../../../header/data/info/Message.h"
#include"../../../../header/data/info/Text.h"
// 获取申请理由（非空+长度限制）
std::string UserApplication::getDormApplyReason()
{
    while (true)
    {
        std::string number = getNonEmptyInput(
            "screen.operation.operations.UserApplication.DormApplyReason.Input.number");
        if (number.size() == 12) break;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.number.error");
        std::cout << std::endl;
    }
    while (true)
    {
        std::string content;
        content = getNonEmptyInput("screen.operation.operations.UserApplication.DormApplyReason.Input");
        if (content.length() <= 50) return content;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.error");
        std::cout << std::endl;
    }
}
