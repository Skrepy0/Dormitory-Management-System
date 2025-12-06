#pragma once
#include "basic/Time.h"
#include "../../source/data/library/json.hpp"

class StayLog {// 住、退宿记录
    nlohmann::json data;// 总数据
    std::string type;// 形式 "check-in" or "check-out"
    Time time;// 办理时间
    std::string id;// 申请人id
    std::string name;// 处理人名字
    nlohmann::json dormitoryData;// 申请人的宿舍详细信息
    nlohmann::json checkInRecords;// 入住列表
     nlohmann::json checkOutRecords;// 退宿列表
    std::string recordId;// 该记录的id值
    void init();
    void addToData();
    static std::string getHash();

public:
    StayLog();
    StayLog(std::string type, Time time,std::string id, std::string name,nlohmann::json dormitoryData);
    StayLog(nlohmann::json data);
    nlohmann::json getData();
    Time getTime();
    std::string getId();
    std::string getName();
    nlohmann::json getDormitoryData();
    nlohmann::json getCheckInRecords();
    nlohmann::json getCheckOutRecords();

    bool writeToFile();// 将该对象的数据存入文件
    static nlohmann::json readJson();// 读取json并返回数据

    void setData(nlohmann::json data);
    void setTime(Time time);
    void setId(std::string id);
    void setName(std::string name);
    void setDormitoryData(nlohmann::json dormitoryData);
    void addCheckInRecords(nlohmann::json checkInRecord);
    void addCheckOutRecords(nlohmann::json checkOutRecord);

};
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
