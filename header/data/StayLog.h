#pragma once
#include "../../header/data/HashHelper.h"
#include "../../source/data/library/json.hpp"
#include "basic/Time.h"
class StayLog {
    // 住、退宿记录
    static nlohmann::json data; // 总数据
    std::string type; // 形式 "check-in" or "check-out"
    Time time{}; // 办理时间
    std::string id; // 申请人id
    std::string name; // 处理人名字
    nlohmann::json dormitoryData; // 申请人的宿舍详细信息
    static nlohmann::json checkInRecords; // 入住列表
    static nlohmann::json checkOutRecords; // 退宿列表
    std::string recordId; // 该记录的id值
    static void init();

    void addToData();

public:
    StayLog();

    StayLog(std::string type, Time time, std::string id, std::string name, nlohmann::json dormitoryData);

    explicit StayLog(nlohmann::json data);
    static nlohmann::json getData();

    Time getTime();

    std::string getId();

    std::string getName(); // 获取处理人名字
    nlohmann::json getDormitoryData(); // 获取宿舍信息
    static nlohmann::json getCheckInRecords(); // 获取入宿列表
    static nlohmann::json getCheckOutRecords(); // 获取退宿列表

    bool writeToFile(); // 将该对象的数据存入文件
    static nlohmann::json readJson(); // 读取json并返回数据

    void setData(nlohmann::json data); // 设置data
    void setTime(Time time); // 设置该记录的时间
    void setId(std::string id); // 获取申请人名字
    void setName(std::string name); // 获取处理人名字
    void setDormitoryData(nlohmann::json dormitoryData); // 设置宿舍信息
    static void addCheckInRecords(nlohmann::json checkInRecord); // 添加入宿记录
    static void addCheckOutRecords(nlohmann::json checkOutRecord); // 添加退宿记录
};

/*
*   nlohmann::json data;
    data["bed_number"] = "4";
    data["building_number"] = "11";
    data["building_name"] = "B";
    data["room_number"] = "312";
    data["reason"] = "入学";
    nlohmann::json checkIn;
    checkIn["time"] = Time().getTime();
    checkIn["handler"] = "123";
    checkIn["initiator"] = "456";
    checkIn["dormitory"] = data;
    StayLog stayLog;
    StayLog::addCheckOutRecords(checkIn);
    std::cout << checkIn.dump(4) << std::endl;
 */

// json格式：
/*
 * {
 *      "check-in":[
 *          {
 *              “time”:{// 处理时间
 *                  "year":2025,
 *                  "month":8,
 *                  "day":25,
 *                  "hour":18,
 *                  "minute":25
 *              }
 *              "handler":"张三",// 处理人
 *              "initiator":"李四",// 申请人
 *              “dormitory”:{
 *                  "bed_number": "4",// 床号
 *                  "building_number": "11",// 楼号
 *                  "room_number": "4",// 房间号
 *                  "building_name":"11栋",// 楼名
 *                  "reason":"入学"// 理由/备注
 *              }
 *          }
 *      ],
 *      "check-out":[
 *          {
 *              “time”:{
 *                  "year":2025,
 *                  "month":8,
 *                  "day":25,
 *                  "hour":18,
 *                  "minute":25
 *              }
 *              "handler":"张三",
 *              "initiator":"李四",
 *              “dormitory”:{
 *                  "bed_number": "4",
 *                  "building_number": "11",
 *                  "room_number": "4",
 *                  "building_name":"11栋",
 *                  "reason":"毕业"
 *              }
 *          }
 *      ],
 * }
 */
