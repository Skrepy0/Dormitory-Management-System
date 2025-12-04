#include <iostream>
#include "../../../header/data/basic/Dormitory.h"

Dormitory::Dormitory(std::string floor, std::string room_number, int vacant_bed, nlohmann::json maintenances) :
	floor(floor), room_number(room_number), vacant_bed(vacant_bed), maintenances(maintenances){
}

bool Dormitory::addMaintenances(Maintenance maintenance) {
	try {
		maintenances.push_back(maintenance.getMaintenanceData());
		return true;
	}
	catch (...) {
		return false;
	}
}

nlohmann::json Dormitory::getDormitoryData() {
	data["floor"] = floor;
	data["room_number"] = room_number;
	data["vacant_bed"] = vacant_bed;
	data["maintenances"] = maintenances;
	return this->data;
}

long long Dormitory::findMaintenanceById(std::string id) {
	if (maintenances.empty())return -1;
	else {
		int index = 0;
		for (auto i : maintenances) {
			if (id == (std::string)i["id"]) {
				return index;
			}
			index++;
		}
	}
	return -1;
}

nlohmann::json Dormitory::getUnsettledMaintenanceList() {
	nlohmann::json jsonList = nlohmann::json::array();
	for (auto i : maintenances) {
		if ((bool)i["state"])jsonList.push_back(i);
	}
	return jsonList;
}

std::string Dormitory::getFloor()
{
	return floor;
}

std::string Dormitory::getRoomNumber()
{
	return room_number;
}

int Dormitory::getVacant_bed()
{
	return vacant_bed;
}

nlohmann::json Dormitory::getMaintencensList()
{
	return maintenances;
}
