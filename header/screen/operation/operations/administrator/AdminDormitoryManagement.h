#pragma once
#include "../../../InputMenu.h"
#include "../../../../data/Accommodations.h"
#include "../../../../data/BuildingData.h"
#include "../../../../data/basic/Dormitory.h"
#include <string>

class AdminDormitoryManagement : public InputMenu {
private:
    static Accommodations& getAccommodations();

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
    //5. 更新宿舍楼信息
    static void inputUpdateBuildingInfo(Accommodations &acc);
    //6. 更新宿舍房间信息
    static void inputUpdateRoomInfo(Accommodations &acc);

};
