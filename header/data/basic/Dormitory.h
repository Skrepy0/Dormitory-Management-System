#pragma once
#include<iostream>
#include"../../../source/data/library/json.hpp"
#include"./Maintenance.h"
class Dormitory {
private:
	nlohmann::json data;
	std::string floor;// 楼层信息
	std::string room_number;// 宿舍号
	int vacant_bed;// 空床位数 
	nlohmann::json maintenances = nlohmann::json::array();// json列表储存报修信息
public:
	Dormitory(std::string floor,
		std::string room_number,
		int vacant_bed,
		nlohmann::json maintenances);
	bool addMaintenances(Maintenance maintenance);
	nlohmann::json getDormitoryData();
	long long findMaintenanceById(std::string id);// 通过id查找维修记录并返回索引
	nlohmann::json getUnsettledMaintenanceList();// 获取未处理的维修记录返回json列表
	std::string getFloor();
	std::string getRoomNumber();
	int getVacant_bed();
	nlohmann::json getMaintencensList();
};


