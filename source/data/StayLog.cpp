#include "../../header/data/StayLog.h"

#include <chrono>
#include <fstream>
#include <utility>

// 定义静态成员变量
nlohmann::json StayLog::data;
nlohmann::json StayLog::checkInRecords;
nlohmann::json StayLog::checkOutRecords;

namespace {
    std::string FILE_PATH = R"(..\data\data\StayLog.json)";
}

void StayLog::init() {
    data = readJson();
    checkInRecords = data["check-in"];
    checkOutRecords = data["check-out"];
}

void StayLog::addToData() {
    recordId = HashHelper::getHashFromCurrentTime();
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

StayLog::StayLog() { init(); }


StayLog::StayLog(std::string type, Time time, std::string id, std::string name, nlohmann::json dormitoryData) :
    type(std::move(type)), time(time), id(std::move(id)), name(std::move(name)),
    dormitoryData(std::move(dormitoryData)) {
    init();
    writeToFile();
}

StayLog::StayLog(nlohmann::json data) {
    checkInRecords = data["check-in"];
    checkOutRecords = data["check-out"];
}

nlohmann::json StayLog::getData() {
    init();
    return data;
}

Time StayLog::getTime() { return this->time; }

std::string StayLog::getId() { return this->id; }

std::string StayLog::getName() { return this->name; }

nlohmann::json StayLog::getDormitoryData() { return dormitoryData; }

nlohmann::json StayLog::getCheckInRecords() {
    init();
    return checkInRecords;
}

nlohmann::json StayLog::getCheckOutRecords() {
    init();
    return checkOutRecords;
}

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

long long StayLog::findStayLogByHash(std::string hash, std::string stayLogType) {
    init();
    for (int i = 0;i < data[stayLogType].size();i++) {
        if (data[stayLogType][i]["hash"] == hash) {
            return i;
        }
    }
    return -1;
}

void StayLog::delStayLog(long long index, std::string stayLogType) {
    init();
    data[stayLogType].erase(index);
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        throw("Error opening file");
    }
    out_file << data.dump(4);
    out_file.close();
}

void StayLog::setDormitoryData(nlohmann::json dormitoryData) { this->dormitoryData = dormitoryData; }

void StayLog::addCheckInRecords(nlohmann::json checkInRecord) {
    init();
    checkInRecord["hash"] = HashHelper::getHashFromCurrentTime();
    checkInRecords.push_back(checkInRecord);
    data["check-in"] = checkInRecords;
    data["check-out"] = checkOutRecords;
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        throw("Error opening file");
    }
    out_file << data.dump(4);
    out_file.close();
}

void StayLog::addCheckOutRecords(nlohmann::json checkOutRecord) {
    init();
    checkOutRecord["hash"] = HashHelper::getHashFromCurrentTime();
    checkOutRecords.push_back(checkOutRecord);
    data["check-in"] = checkInRecords;
    data["check-out"] = checkOutRecords;
    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        throw("Error opening file");
    }
    out_file << data.dump(4);
}
