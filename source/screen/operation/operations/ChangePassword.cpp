#include "../../../../header/screen/operation/operations/ChangePassword.h"
#include"../../../../header/data/info/Message.h"
#include"../../../../header/data/info/Text.h"

std::string ChangePassword::changePassword(const std::string& Password)
{
    std::string currentPassword;
    Text t(Password);
    currentPassword = t.getContent();
    std::string oldPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.original_password.Input.");

    // 原密码不匹配：调用父类showError显示错误提示
    if (oldPwd != currentPassword)
    {
        showError("screen.operation.operations.UserChangePassword.original_password.Input.error"); // 复用InputMenu的showError方法
        return currentPassword; // 验证失败，返回原密码
    }


    // ========== 2. 输入新密码（非空校验） ==========
    std::string newPwd;
    while (true)
    {
        newPwd = getNonEmptyInput("screen.operation.operations.UserChangePassword.new_password.Input");
        if (!newPwd.empty())
        {
            break; // 新密码非空则跳出循环
        }
        // 新密码为空：显示错误提示
        showError("screen.operation.operations.UserChangePassword.new_password.empty");
    }


    // ========== 3. 二次确认新密码 ==========
    std::string confirmPwd =
        getNonEmptyInput("screen.operation.operations.UserChangePassword.new_password.Input.again");

    // 两次输入不一致：显示错误提示
    if (newPwd != confirmPwd)
    {
        showError("screen.operation.operations.UserChangePassword.new_password.difference");
        return currentPassword;
    }


    // ========== 4. 最终确认是否修改 ==========
    // 调用父类confirmOperation获取用户确认（Y/N）
    bool isConfirm = confirmOperation("screen.operation.operations.UserChangePassword.new_password.confirmation");
    if (isConfirm)
    {
        // 修改成功：调用父类showSuccess显示成功提示
        showSuccess("screen.operation.operations.UserChangePassword.new_password.success");
        return newPwd; // 返回新密码（后续可更新到学生信息中）
    }
    else
    {
        // 取消修改：显示提示
        showContent("screen.operation.operations.UserChangePassword.new_password.fail");
        return currentPassword;
    }
}
