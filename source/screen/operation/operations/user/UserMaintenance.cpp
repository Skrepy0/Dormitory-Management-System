#include "../../../../../header/screen/operation/operations/user/UserMaintenance.h"
#include <chrono>
#include <cstdio>
#include <ctime>
#include <iomanip>
#include "../../../../../header/data/basic/Time.h"
#include "../../../../../header/data/info/Text.h"

std::string UserMaintenance::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
    std::tm localTime = *std::localtime(&currentTime);

    char timeBuf[64];
    std::strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S", &localTime);
    return std::string(timeBuf);
}


void UserMaintenance::submitRepair() {
    showTitle("screen.operation.operations.UserMaintenance.title");
    std::cout << std::endl;


    sponsor = getNonEmptyInput("screen.operation.operations.UserMaintenance.sponsor");
    description = getNonEmptyInput("screen.operation.operations.UserMaintenance.repair.content");
    bool isConfirm = confirmOperation("screen.operation.operations.UserMaintenance.repair.confirmation");
    if (isConfirm)
        showSuccess("screen.operation.operations.UserMaintenance.repair.success");
    else
        showError("screen.operation.operations.UserMaintenance.repair.error");

    std::string currentTimeStr = getCurrentTime();
    int year, month, day, hour, minute, second;

    if (sscanf(currentTimeStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second) != 6) {
        showError("screen.operation.operations.UserMaintenance.time_format.error");
        return;
    }
    try {
        reportTime = Time(year, month, day, hour, minute, second);
    } catch (const std::invalid_argument &e) {
        showError("screen.operation.operations.UserMaintenance.repair_time.error");
        return;

        try {
            repairTime = Time(2000, 1, 1, 0, 0, 0); // 初始化为合法默认值（后续由管理员修改）
        } catch (const std::invalid_argument &e) {
            showError("screen.operation.operations.UserMaintenance.repair_time.error"); // 去掉message:前缀
            return;
        }

        repairer = "";
        state = false;
        valuation = "";
    }
}
