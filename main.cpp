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
    nlohmann::json data;
    data["bed_number"] = "4";
    data["building_number"] = "11";
    data["building_name"] = "B";
    data["room_number"] = "312";
    data["reason"] = "入学";
    nlohmann::json checkIn;
    checkIn["time"] = Time(2025,5,21,11,28,10).getTime();
    checkIn["handler"] = "123";
    checkIn["initiator"] = "456";
    checkIn["dormitory"] = data;
    StayLog stayLog;
    stayLog.addCheckOutRecords(checkIn);
    stayLog.writeToFile();
    std::cout << checkIn.dump(4) << std::endl;
    system("pause");
}
