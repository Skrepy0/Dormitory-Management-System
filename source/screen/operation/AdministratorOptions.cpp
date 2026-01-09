#include "../../../header/screen/operation/AdministratorOptions.h"
#include <regex>
#include "../../../header/data/info/Message.h"
#include "../../../header/data/info/Text.h"

// 显示管理员主菜单
void AdminOptions::showAdminMainMenu() {
    showTitle("管理员功能菜单");
    std::cout << std::endl;
    showPrompt("1. 宿舍管理");
    std::cout << std::endl;
    showPrompt("2. 申请审核");
    std::cout << std::endl;
    showPrompt("3. 学生信息管理");
    std::cout << std::endl;
    showPrompt("4. 修改管理员密码");
    std::cout << std::endl;
    showPrompt("5. 返回登录页");
    std::cout << std::endl;
    showPrompt("6. 退出系统");
    std::cout << std::endl;
    showPrompt("---------------------------------");
}

// 显示宿舍管理子菜单
void AdminOptions::showAdminDormManageSubMenu() {
    showTitle("宿舍管理");
    showPrompt("1. 新增宿舍信息");
    std::cout << std::endl;
    showPrompt("2. 修改宿舍状态");
    std::cout << std::endl;
    showPrompt("3. 查询宿舍占用情况");
    std::cout << std::endl;
    showPrompt("4. 返回上一级");
    std::cout << std::endl;
    showPrompt("---------------------------------");
    std::cout << std::endl;
}

// 显示审核子菜单
void AdminOptions::showAdminAuditSubMenu() {
    showTitle("申请审核");
    showPrompt("1. 审核退宿申请");
    std::cout << std::endl;
    showPrompt("2. 审核调宿申请");
    std::cout << std::endl;
    showPrompt("3. 审核报修申请");
    std::cout << std::endl;
    showPrompt("4. 返回上一级");
    std::cout << std::endl;
    showPrompt("---------------------------------");
    std::cout << std::endl;
}

// 获取管理员账号（专属校验：6位纯数字）
std::string AdminOptions::getAdminIdInput() { return getDigitInput("请输入管理员账号：", 6, 6); }

// 获取宿舍号（专属格式校验：X号楼XXX室）
std::string AdminOptions::getDormNumInput() {
    std::string dormNum;
    std::regex pattern(R"(\d+号楼\d+室)"); // 正则匹配"X号楼XXX室"格式
    while (true) {
        dormNum = getInput("请输入宿舍号（格式：X号楼XXX室）：");
        if (regex_match(dormNum, pattern))
            return dormNum;
        showError("宿舍号格式错误！示例：1号楼201室");
    }
}

// 获取审核意见（非空+长度限制）
std::string AdminOptions::getAuditOpinionInput() {
    std::string opinion;
    while (true) {
        opinion = getInput("请输入审核意见（最多30字）：");
        if (opinion.length() <= 30)
            return opinion;
        showError("意见长度不能超过30字！");
    }
}

// 展示宿舍列表信息（专属格式）
void AdminOptions::showDormList(const std::string &building, const std::string &freeCount,
                                const std::string &totalCount) {
    showTitle("宿舍占用情况");
    showPrompt("楼栋：");
    showContent(building);
    std::cout << std::endl;
    showPrompt("总房间数：");
    showContent(totalCount);
    std::cout << std::endl;
    showPrompt("空闲房间数：");
    showContent(freeCount);
    std::cout << std::endl;
    // 1. 将string转为int（处理空字符串或非数字的情况）
    int total = 0;
    int free = 0;
    try {
        total = std::stoi(totalCount); // 字符串转int
        free = std::stoi(freeCount);
    } catch (const std::invalid_argument &) {
        // 若转换失败（非数字），默认设为0
        total = 0;
        free = 0;
    } catch (const std::out_of_range &) {
        // 数值超出int范围，默认设为0
        total = 0;
        free = 0;
    }

    // 2. 三目运算符：处理总房间数为0的情况（避免除以0）
    double occupancyRate = (total == 0) ? 0.0 : (static_cast<double>(total - free) * 100.0 / total);

    // 3. 输出入住率
    showPrompt("入住率：");
    showContent(std::to_string(occupancyRate)); // 数值转string
    showContent("%");
    std::cout << std::endl;

    showPrompt("-------------------------------");
    std::cout << std::endl;
}

// 展示学生申请列表（专属格式）
void AdminOptions::showStudentApplyList(const std::string &id, const std::string &name, const std::string &applyType) {
    showTitle("待审核申请列表");
    Message message(Text::of("学生学号："));
    message.printContent();
    showPrompt(id);
    std::cout << std::endl;
    Message message1(Text::of("学生姓名："));
    message1.printContent();
    showPrompt(name);
    std::cout << std::endl;
    Message message2(Text::of("申请类型："));
    message2.printContent();
    showPrompt(applyType);
    std::cout << std::endl;
    Message message3(Text::of("---------------------------------"));
    message3.printContent();
    std::cout << std::endl;
}

// 展示审核结果（专属格式）
void AdminOptions::showAuditResult(const std::string &id, const std::string &applyType, const std::string &result) {
    showSuccess("审核完成！");
    Message message(Text::of("学生学号："));
    message.printContent();
    showPrompt(id);
    std::cout << std::endl;
    Message message1(Text::of("申请类型："));
    message1.printContent();
    showPrompt(applyType);
    std::cout << std::endl;
    Message message2(Text::of("审核结果："));
    message2.printContent();
    showPrompt(result);
    std::cout << std::endl;
    Message message3(Text::of("---------------------------------"));
    message3.printContent();
    std::cout << std::endl;
}
