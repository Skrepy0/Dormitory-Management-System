#pragma once
#include <iostream>
#include "../../source/data/library/json.hpp"
class UserData {
private:
	nlohmann::json data;
	std::string name;
	std::string password;
	std::string email;
	std::string building_number;
	std::string room_number;
	std::string bed_number;
	std::string id;
	void init();
	void addToData();
	static bool compareDormitory(nlohmann::json dormitory_1, nlohmann::json dormitory_2);
	size_t getHash(std::string str);
public:
	UserData();
	UserData(std::string name,
		std::string id,
		std::string password,
		std::string email,
		std::string building_number,
		std::string room_number,
		std::string bed_number);
	
	static void addFromJson(nlohmann::json userData);// 通过json直接添加用户数据
	nlohmann::json getData();// 获取对象的数据
	void setData(nlohmann::json userData);// 设置对象的数据
	bool writeToFile();// 将该对象的数据存入文件
	static nlohmann::json readJson();// 读取UserData.json并返回数据
	static long long findUserByName(std::string name);// 最好别用，可能重名
	static long long findUserById(std::string id);// 通过学号查找用户，返回在"user"列表的索引
	static long long findUserByDormitory(nlohmann::json dormitory);// 通过宿舍查找用户，返回在"user"列表的索引

	static bool eraseUserById(std::string id);// 通过学号删除用户，删除成功则返回true，失败则返回false
	static bool eraseUserByDormitory(nlohmann::json dormitory);// 通过宿舍删除用户，删除成功则返回true，失败则返回false
};

/*
	使用前务必先熟悉json语法，和nlohmann::json的用法，毕竟json是本项目数据的主要储存形式
	

	一：写入数据：
	使用方法：
	1.
	UserData user("name","password","email"...); 会直接添加用户信息
--------------------------------------------------------------------
	2.
	nlohmann::json newData;

	...对newData操作...
	如：
	newData["name"] = "name";
	newData["password"] = "password"; // 注意：实际应用中密码应该加密存储
	newData["email"] = "email";

	nlohmann::json dormitoryData;
	dormitoryData["bed_number"] = "bed_number";
	dormitoryData["building_number"] = "building_number";
	dormitoryData["room_number"] = "room_number";

	newData["dormitory"] = dormitoryData;

	UserData::addFromJson(newData);
---------------------------------------------------------------------
	3.
	json newdata;
	...对newData操作...
    json data;
    data["user"].push_back(newdata);
    UserData user = UserData();
    user.setData(data);
    user.writeToFile();
-----------------------------------------------------------------------
	二：访问数据：
	nlohmann::json newData=user.getData();
	...对newData进行访问的操作...
*/ 