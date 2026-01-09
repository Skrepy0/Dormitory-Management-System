//
// Created by Skrepy on 2026/1/5.
//

#pragma once
#include "../../../SelectMenu.h"

class DormitoryManageMenu : public SelectMenu {
private:
    static void jumpInputAddBuilding();
    static void jumpInputDeleteBuilding();
    static void jumpInputAddDorm();
    static void jumpInputDeleteDorm();
    static void jumpUpdateBuildingInfo();
    static void jumpUpdateDormInfo();

public:
    DormitoryManageMenu();
    void loop();
};
