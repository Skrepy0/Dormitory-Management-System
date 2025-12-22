#include<iostream>
#include<vector>
#include"./header/data/info/Text.h"
#include"./header/data/Accommodations.h"
#include"./header/data/BuildingData.h"
#include"./header/data/UserData.h"
#include "header/data/StayLog.h"
#include "header/data/info/Message.h"
#include <windows.h>


int main() {
    BuildingData building("123", "loa", "001", "114514", "123");
    building.addDormitory(Dormitory("3", "312", 0, Maintenance(Time(), Time(), "asda", "des", "lis", true, "good", "0x123f5d").getMaintenanceData()));
    Accommodations acc;
    acc.addBuildings(building);
    acc.writeInFile();
    return 0;
}
