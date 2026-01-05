#pragma once
#include <string>
#include "../InputMenu.h"

// 管理员专属输入输出类（继承BaseOptions）
class AdminOptions : public InputMenu {
public:
    // 管理员菜单显示（专属）
    void showAdminMainMenu();
    void showAdminDormManageSubMenu();
    void showAdminAuditSubMenu();

    // 管理员专属输入（带业务校验）
    std::string getAdminIdInput(); // 获取管理员账号（6位纯数字）
    std::string getDormNumInput(); // 获取宿舍号（格式：X号楼XXX室）
    std::string getAuditOpinionInput(); // 获取审核意见

    // 管理员专属输出（信息展示）
    void showDormList(const std::string &building, const std::string &freeCount, const std::string &totalCount);
    void showStudentApplyList(const std::string &id, const std::string &name, const std::string &applyType);
    void showAuditResult(const std::string &id, const std::string &applyType, const std::string &result);
};
/*这个应用和学生的基本一样,都是那三类，我也是只有再展示的函数中加入了换行
 *其他换行要是后面需要再加，应为这个和message不一样，这个我写完了基本以上就定型了
 *也就后面调用一下，但是那个颜色我还是没写，到时候再加就行，我也只写可基本的，到时候有其他文本的话我再加
 */
