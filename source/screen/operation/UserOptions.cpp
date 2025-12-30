#include "../../../header/screen/operation/UserOptions.h"
#include"../../../header/data/info/Message.h"
#include"../../../header/data/info/Text.h"
// 显示学生主菜单
void StudentOptions::showStudentMainMenu()
{
    showTitle("学生功能菜单");
    std::cout << std::endl;
    Message message(Text::of("1. 宿舍信息查询"));
    message.printContent();
    std::cout << std::endl;
    Message message1(Text::of("2. 申请操作"));
    message1.printContent();
    std::cout << std::endl;
    Message message2(Text::of("3. 修改个人密码"));
    message2.printContent();
    std::cout << std::endl;
    Message message3(Text::of("4. 返回登录页"));
    message3.printContent();
    std::cout << std::endl;
    Message message4(Text::of("5. 退出系统"));
    message4.printContent();
    std::cout << std::endl;
    Message message5(Text::of("---------------------------------"));
    message5.printContent();
    std::cout << std::endl;
}

// 显示学生查询子菜单
void StudentOptions::showStudentQuerySubMenu()
{
    showTitle("宿舍信息查询");
    std::cout << std::endl;
    Message message(Text::of("1. 查看我的宿舍信息"));
    message.printContent();
    std::cout << std::endl;
    Message message1(Text::of("2. 查看申请记录"));
    message1.printContent();
    std::cout << std::endl;
    Message message2(Text::of("3. 查看缴费记录"));
    message2.printContent();
    std::cout << std::endl;
    Message message3(Text::of("4. 返回上一级"));
    message3.printContent();
    std::cout << std::endl;
    Message message4(Text::of("---------------------------------"));
    message4.printContent();
    std::cout << std::endl;
}

// 显示学生申请子菜单
void StudentOptions::showStudentApplySubMenu()
{
    showTitle("申请操作");
    std::cout << std::endl;
    Message message(Text::of("1. 提交退宿申请"));
    message.printContent();
    std::cout << std::endl;
    Message message1(Text::of("2. 提交调宿申请"));
    message1.printContent();
    std::cout << std::endl;
    Message message2(Text::of("3. 提交设施报修"));
    message2.printContent();
    std::cout << std::endl;
    Message message3(Text::of("4. 返回上一级"));
    message3.printContent();
    std::cout << std::endl;
    Message message4(Text::of("---------------------------------"));
    message4.printContent();
    std::cout << std::endl;
}

// 获取学号（专属校验：8位纯数字）
std::string StudentOptions::getStudentIdInput()
{
    return getDigitInput("请输入您的学号：", 12, 12);
}

// 获取申请理由（非空+长度限制）
std::string StudentOptions::getDormApplyReason()
{
    std::string reason;
    while (true)
    {
        reason = getNonEmptyInput("请输入申请理由（最多50字）：");
        if (reason.length() <= 50) return reason;
        showError("理由长度不能超过50字！");
    }
}

// 获取报修内容
std::string StudentOptions::getRepairContentInput()
{
    return getNonEmptyInput("请描述报修设施及问题：");
}

// 展示学生宿舍信息（专属格式）
void StudentOptions::showStudentDormInfo(const std::string& id, const std::string& dormNum,
                                         const std::string& checkInTime)
{
    showTitle("我的宿舍信息");
    Message message(Text::of("学号："));
    message.printContent();
    showPrompt(id);
    Message message1(Text::of("宿舍号："));
    message1.printContent();
    showPrompt(dormNum);
    Message message2(Text::of("入住时间："));
    message2.printContent();
    showPrompt(checkInTime);
    Message message3(Text::of("---------------------------------"));
    message3.printContent();
}

// 展示申请状态（专属格式）
void StudentOptions::showApplyStatus(const std::string& applyType, const std::string& status,
                                     const std::string& auditMsg)
{
    showTitle("申请状态查询");
    Message message(Text::of("申请类型："));
    message.printContent();
    showPrompt(applyType);
    Message message1(Text::of("审核状态："));
    message1.printContent();
    showPrompt(status);
    Message message2(Text::of("审核备注："));
    message2.printContent();
    showPrompt(auditMsg.empty() ? "暂无" : auditMsg);
    Message message3(Text::of("---------------------------------"));
    message3.printContent();
}
