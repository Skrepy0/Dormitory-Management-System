#pragma once
#include <string>
#include "../InputMenu.h"

// 学生专属输入输出类（继承BaseOptions）

class StudentOptions : public InputMenu {
public:
    // 学生菜单显示（专属）
    void showStudentMainMenu(); // 展示学生菜单具体功能
    void showStudentQuerySubMenu(); // 展示宿舍信息查询的具体功能
    void showStudentApplySubMenu(); // 展示申请操作的具体功能

    // 学生专属输入（带业务校验）
    std::string getStudentIdInput(); // 获取学号（固定12位）
    std::string getDormApplyReason(); // 获取申请理由（退宿/调宿）
    std::string getRepairContentInput(); // 获取报修内容

    // 学生专属输出（信息展示）
    void showStudentDormInfo(const std::string &id, const std::string &dormNum, const std::string &checkInTime);
    // 这个是展示宿舍信息的，分别对应学号，宿舍号，以及入住时间
    void showApplyStatus(const std::string &applyType, const std::string &status, const std::string &auditMsg);
    // 这个是展示审查状态查询的，分别对应申请类型，审核状态以及申请备注
};

/*目前我只把基本的写出来了，如果后面还有文本那就再加
 *我只把展示部分加了必要的换行，其他各种输出基本上都没有，因为操作页面还没有设计出来
 *这样会导致输出的可能都在一行，但是没关系，我想先把文本给做出来，到时候还要再加上那的选项设计
 *加上之后设计好，我再把所有换行加上，那个文本不是要储存在一个文件中吗，我想先输出出来到时候要是需要改
 *我再把所有文本改一下，那其实也挺好改的，都是些重复性的活了
 *并且这些文本的颜色本来都要再加工一下，我没有添加颜色，到时候加几个符号就行了
 *颜色还要再讨论一下
 *这个使用其实挺好用的，主要分为展示，输入和输出，这个输学号我是按咱们自己学号的长度设计的，如果输出有误，都会有提示的
 *其他的就没啥了，输出的文本都在cpp中一眼都看出来了，到时候有啥需要改的说一下就行
 */
