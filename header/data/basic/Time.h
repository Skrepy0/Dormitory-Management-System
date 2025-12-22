#pragma once
#include <iostream>
#include<stdexcept>
#include "../../../source/data/library/json.hpp"
class Time {// 包含年月日和24小时制的时间
private:
	int year;  // 年
	int month;  // 月
	int day;  // 日
	int hour;  // 时
	int minute;  // 分
	int second;	 // 秒
public:
	// 储存格式参见DormitoryData.json
	Time(int year, int month, int day, int hour, int minute, int second);
	nlohmann::json getTime();// 储存为json（object）返回
};
//该部分主要用于记录时间，通过Time::Time(a,b,c,d,e,f)对所要定义的时间进行赋值