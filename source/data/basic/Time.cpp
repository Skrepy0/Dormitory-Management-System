#include "../../../header/data/basic/Time.h"
Time::Time(int year, int month, int day, int hour, int minute, int second)
	: year(year), month(month), day(day), hour(hour), minute(minute), second(second)
{
	if (year < 0 || month < 0 || day < 0 || hour < 0 || minute < 0 || second < 0||month > 12|| day > 31||hour > 24||minute > 60||second > 60)
        throw std::invalid_argument("Invalid time value");  //只有当输出的参数合理时才会继续执行下面的代码，否则抛出异常
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
