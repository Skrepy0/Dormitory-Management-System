#include "../../header/data/StayLog.h"

#include <chrono>
#include <fstream>
#include <sstream>

namespace {
    std::string FILE_PATH;
}

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S");
    ss << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}

// 简单哈希函数（将字符串转换为哈希值）
std::string simpleHashString(const std::string &input) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(input);

    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}

void StayLog::init() {
    FILE_PATH = R"(..\data\data\StayLog.json)";
    this->data = readJson();
    checkInRecords = data["check-in"];
    checkOutRecords = data["check-out"];
}

void StayLog::addToData() {
    recordId = getHash();
    if (type == "check-in") {
        nlohmann::json checkInData;
        checkInData["time"] = time.getTime();
        checkInData["handler"] = name;
        checkInData["initiator"] = id;
        checkInData["dormitory"] = dormitoryData;
        checkInData["hash"] = recordId;
        checkInRecords.push_back(checkInData);
    } else if (type == "check-out") {
        nlohmann::json checkOutData;
        checkOutData["time"] = time.getTime();
        checkOutData["handler"] = name;
        checkOutData["initiator"] = id;
        checkOutData["dormitory"] = dormitoryData;
        checkOutData["hash"] = recordId;
        checkOutRecords.push_back(checkOutData);
    }
    data["check-in"] = checkInRecords;
    data["check-out"] = checkOutRecords;
}

std::string StayLog::getHash() { return simpleHashString(getCurrentTimestamp()); }

StayLog::StayLog() { init(); }


StayLog::StayLog(std::string type, Time time, std::string id, std::string name, nlohmann::json dormitoryData) :
    type(type), time(time), id(id), name(name), dormitoryData(dormitoryData) {
    init();
    writeToFile();
}

StayLog::StayLog(nlohmann::json data) : data(data) {}

nlohmann::json StayLog::getData() { return data; }

Time StayLog::getTime() { return this->time; }

std::string StayLog::getId() { return this->id; }

std::string StayLog::getName() { return this->name; }

nlohmann::json StayLog::getDormitoryData() { return dormitoryData; }

nlohmann::json StayLog::getCheckInRecords() { return checkInRecords; }

nlohmann::json StayLog::getCheckOutRecords() { return checkOutRecords; }

bool StayLog::writeToFile() {
    addToData();
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return false;
    }
    out_file << data.dump(4);
    out_file.close();
    return true;
}

nlohmann::json StayLog::readJson() {
    std::ifstream in_file(FILE_PATH);
    nlohmann::json newData = nlohmann::json::parse(in_file);
    in_file.close();
    return newData;
}

void StayLog::setData(nlohmann::json data) { this->data = data; }

void StayLog::setTime(Time time) { this->time = time; }

void StayLog::setId(std::string id) { this->id = id; }

void StayLog::setName(std::string name) { this->name = name; }

void StayLog::setDormitoryData(nlohmann::json dormitoryData) { this->dormitoryData = dormitoryData; }

void StayLog::addCheckInRecords(nlohmann::json checkInRecord) {
    checkInRecord["hash"] = getHash();
    checkInRecords.push_back(checkInRecord);
}

void StayLog::addCheckOutRecords(nlohmann::json checkOutRecord) {
    checkOutRecord["hash"] = getHash();
    checkOutRecords.push_back(checkOutRecord);
}
