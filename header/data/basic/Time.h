#pragma once
#include <iostream>
#include "../../../source/data/library/json.hpp"
class Time {// 包含年月日和24小时制的时间

public:
	nlohmann::json getTime();// 储存为json（object）返回
	// 储存格式参见DormitoryData.json
};