#pragma once
#include<iostream>
#include"../../source/data/library/json.hpp"
#include"./BuildingData.h"
#include <unordered_map>
class Accommodations {
private:
	nlohmann::json data;// DormitoryData.json里的所有数据
	void init();
public:
	Accommodations();
	void addBulidings(BuildingData data);// 添加宿舍楼
	static long long findBulidingByName(std::string name);// 通过宿舍楼的名字来查找宿舍楼，并返回索引
	static long long findBulidingByNumber(std::string number);// 通过楼号查找宿舍楼，并返回索引
	static long long findBulidingByLocation(std::string location);// 通过位置信息查找宿舍楼，并返回索引
	static nlohmann::json readFromJson();// 读取DormitoryData.json里的所有数据
	bool writeInFile();// 将当前信息写入DormitoryData.json(密码以哈西值的方式存储)
	nlohmann::json getBuildingJson(int index);// 通过索引获取宿舍楼信息

	// O(1) maps: location/name/number -> index
	static std::unordered_map<std::string, long long> locationIndexMap;
	static std::unordered_map<std::string, long long> nameIndexMap;
	static std::unordered_map<std::string, long long> numberIndexMap;
	static void buildIndexMaps();
};

/*使用示例：
*	ps:写代码时建议打开内联提示
* 
*	1.添加：
	BuildingData building("123", "loa", "001", "114514", "123");
	building.addDormitory(Dormitory("3", "312", 0, Maintenance(Time(), Time(), "asda", "des", "lis", true, "good", "0x123f5d").getMaintenanceData()));
	Accommodations acc;
	acc.addBulidings(building);
	acc.writeInFile();
	---------------------------------------------------------------------------------------------
	2.查找
	Accommodations acc;
	std::cout << acc.getBuildingJson(Accommodations::findBulidingByName("building_name"));

*/