#include "../../../../../header/screen/operation/operations/user/UserApplication.h"
#include "../../../../../header/data/info/Message.h"
#include "../../../../../header/data/info/Text.h"
// 获取申请理由（非空+长度限制）
std::string UserApplication::getDormApplyReason() {
    std::string reason;
    while (true) {
        reason = getNonEmptyInput("screen.operation.operations.UserApplication.DormApplyReason.Input");
        if (reason.length() <= 50)
            return reason;
        showError("screen.operation.operations.UserApplication.DormApplyReason.Input.error");
    }
}
// 获取报修内容
