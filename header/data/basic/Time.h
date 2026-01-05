#pragma once
#include <iostream>
#include<stdexcept>
#include "../../../source/data/library/json.hpp"

class Time
{
    // 包含年月日和24小时制的时间
private:
    int year; // 年
    int month; // 月
    int day; // 日
    int hour; // 时
    int minute; // 分
    int second; // 秒
public:
    Time() = default;
    // 储存格式参见DormitoryData.json
    Time(int year, int month, int day, int hour, int minute, int second);
    nlohmann::json getTime(); // 储存为json（object）返回
    static Time getCurrentTime(); // 系统自动记录当前时间
};

//该部分主要用于记录时间，通过Time::Time(a,b,c,d,e,f)对所要定义的时间进行赋值
//新加的这个函数能够直接返回一个Time类的参数，用于记录当前时间
