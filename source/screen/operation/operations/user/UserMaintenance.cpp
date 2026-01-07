/**
 * @file UserMaintenance.h
 * @brief 用户维修相关功能的实现文件
 */
#include "../../../../../header/screen/operation/operations/user/UserMaintenance.h"
#include <chrono> // 用于处理时间相关操作
#include <cstdio> // 用于C风格输入输出
#include <ctime> // 用于时间函数
#include <iomanip> // 用于格式化输出
#include <windows.h>

// 引入各种数据结构类
#include "../../../../../header/data/Accommodations.h"
#include "../../../../../header/data/DataHelper.h"
#include "../../../../../header/data/HashHelper.h"
#include "../../../../../header/data/UserData.h"
#include "../../../../../header/data/basic/Maintenance.h"
#include "../../../../../header/data/basic/Time.h"

/**
 * @brief 上报新的维修记录
 * 该方法创建一个新的维修记录，并将其保存到相应的宿舍房间数据中
 */
void init() {
    // TODO: 初始化操作
}
void UserMaintenance::upLoadNewMaintenance() {
    // 创建维修记录对象，包含报告时间、维修时间、发起人、描述等信息
    Maintenance maintenance(reportTime, repairTime, sponsor, description, repairer, false, "",
                            HashHelper::getHashFromCurrentTime());
    // 读取用户数据并找到当前用户
    nlohmann::json userData = DataHelper::getUser("123");// TODO 换成user-id
    // 根据宿舍号找到对应的建筑索引
    long long buildingIndex = Accommodations::findBuildingByNumber(DataHelper::getDormitory(userData)["building_number"]);
    // 读取建筑数据并找到对应的宿舍房间
    nlohmann::json buildingData = DataHelper::getDormitoryBuildingList()[buildingIndex];
    // 遍历建筑中的所有房间，找到当前用户所在的房间
    for (auto &room: buildingData["dormitories"]) {
        if (room["room_number"] == userData["dormitory"]["room_number"]) {
            // 将维修记录添加到房间的维修列表中
            room["maintenances"].push_back(maintenance.getMaintenanceData());
            break;
        }
    }
    // 创建新的住宿对象，更新建筑数据并保存到文件
    Accommodations newAccommodations;
    newAccommodations.eraseBuilding(buildingIndex);
    newAccommodations.addBuildings(BuildingData(buildingData));
    newAccommodations.writeInFile();
}

/**
 * @brief 获取当前系统时间
 * @return 返回格式化的时间字符串（格式：YYYY-MM-DD HH:MM:SS）
 */
std::string UserMaintenance::getCurrentTime() {
    // 获取当前系统时间点
    auto now = std::chrono::system_clock::now();
    // 转换为time_t格式
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    // 转换为本地时间
    std::tm localTime = *std::localtime(&currentTime);

    // 格式化时间字符串
    char timeBuf[64];
    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &localTime);
    return std::string(timeBuf);
}


/**
 * @brief 提交维修申请
 * 该方法收集用户的维修信息，包括维修内容、发起人等，并创建维修记录
 */
void UserMaintenance::submitRepair() {

    // 显示维修申请标题
    showTitle("screen.operation.operations.UserMaintenance.title");
    std::cout << std::endl;


    // 获取维修发起人信息
    sponsor = getNonEmptyInput("screen.operation.operations.UserMaintenance.sponsor");
    // 获取维修描述信息
    description = getNonEmptyInput("screen.operation.operations.UserMaintenance.repair.content");
    // 确认是否提交维修申请
    bool isConfirm = confirmOperation("screen.operation.operations.UserMaintenance.repair.confirmation");
    if (isConfirm) {
        showSuccess("screen.operation.operations.UserMaintenance.repair.success");
        pause();
    } else {
        showError("screen.operation.operations.UserMaintenance.repair.error");
        pause();
    }

    std::string currentTimeStr = getCurrentTime();
    int year, month, day, hour, minute, second;

    if (sscanf(currentTimeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        showError("screen.operation.operations.UserMaintenance.time_format.error");
        pause();
        return;
    }
    try {
        reportTime = Time(year, month, day, hour, minute, second);
    } catch (const std::invalid_argument &e) {
        showError("screen.operation.operations.UserMaintenance.repair_time.error");
        pause();
        return;

        try {
            repairTime = Time(2000, 1, 1, 0, 0, 0); // 初始化为合法默认值（后续由管理员修改）
        } catch (const std::invalid_argument &e) {
            showError("screen.operation.operations.UserMaintenance.repair_time.error");
            pause();
            return;
        }

        repairer = "";
        state = false;
        valuation = "";
    }
    upLoadNewMaintenance();
}
