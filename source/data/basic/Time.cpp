#include "../../../header/data/basic/Time.h"
#include <chrono>
#include <ctime>

Time::Time(int year, int month, int day, int hour, int minute, int second)
    : year(year), month(month), day(day), hour(hour), minute(minute), second(second)
{
    if (year < 0 || month < 0 || day < 0 || hour < 0 || minute < 0 || second < 0 || month > 12 || day > 31 || hour > 24
        || minute > 60 || second > 60)
        throw std::invalid_argument("Invalid time value"); //只有当输出的参数合理时才会继续执行下面的代码，否则抛出异常
}

nlohmann::json Time::getTime()
{
    nlohmann::json data;
    data["year"] = year;
    data["month"] = month;
    data["day"] = day;
    data["hour"] = hour;
    data["minute"] = minute;
    data["second"] = second;
    return data;
}

Time Time::getCurrentTime()
{
    auto currentSystemTime = std::chrono::system_clock::now();


    std::time_t timeStamp = std::chrono::system_clock::to_time_t(currentSystemTime);

    std::tm* localTimeInfo = std::localtime(&timeStamp);


    int year = localTimeInfo->tm_year + 1900; // 年份 = 1900 + tm_year
    int month = localTimeInfo->tm_mon + 1; // 月份 = 1 + tm_mon（tm_mon是0开始）
    int day = localTimeInfo->tm_mday; // 日期（直接用tm_mday）
    int hour = localTimeInfo->tm_hour; // 小时（24小时制）
    int minute = localTimeInfo->tm_min; // 分钟
    int second = localTimeInfo->tm_sec; // 秒


    return Time(year, month, day, hour, minute, second);
}
