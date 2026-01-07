#pragma once
#include "../../../InputMenu.h"
#include"../../../../data/BuildingData.h"
#include <string>

class AdminDormitoryManagement : public InputMenu {
private:
    BuildingData getBuildingByNumber(const std::string& buildingNumber);

public:
    static void inputAddBuilding();    // 添加宿舍楼
    void inputAddDorm();        // 添加宿舍
    void inputUpdateBuilding(); // 更新宿舍楼信息
    void inputUpdateDormBed();  // 更新宿舍床位
    void inputDeleteDorm();     // 删除宿舍
};