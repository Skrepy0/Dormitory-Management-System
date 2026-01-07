//
// Created by Skrepy on 2026/1/6.
//

#include "../../header/data/HashHelper.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <sstream>
size_t HashHelper::getHash(std::string str) {
    std::hash<std::string> hasher;
    size_t hash_value = hasher(str);
    return hash_value;
}
std::string HashHelper::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%Y%m%d%H%M%S");
    ss << std::setfill('0') << std::setw(3) << ms.count();

    return ss.str();
}
std::string HashHelper::simpleHashString(const std::string &input) {
    std::hash<std::string> hash_fn;
    size_t hash = hash_fn(input);
    std::stringstream ss;
    ss << std::hex << hash;
    return ss.str();
}
std::string HashHelper::getHashFromCurrentTime() { return simpleHashString(getCurrentTimestamp()); }
