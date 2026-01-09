#pragma once
#include <string>
#include "../../../../data/Accommodations.h"
#include "../../../../data/BuildingData.h"
#include "../../../../data/basic/Dormitory.h"
#include "../../../InputMenu.h"

class AdminDormitoryManagement : public InputMenu {
private:
    static Accommodations &getAccommodations();

    static bool isBuildingOccupied(const std::string &buildingNumber);

public:
    // 1. 添加宿舍楼
    static void inputAddBuilding();
    // 2. 添加宿舍房间
    static void inputAddDormRoom();
    // 3. 删除宿舍楼
    static void inputDeleteBuilding();
    // 4. 删除宿舍房间
    static void inputDeleteDormRoom();
    // 5、展示宿舍楼信息
    static void showBuildingCurrentInfo();
    // 6、展示宿舍信息
    static void showDormCurrentInfo();
    // 7. 更新宿舍楼信息
    static void updateDormitoryBuilding();
    // 8. 更新宿舍房间信息
    static void updateDormitory();
};
