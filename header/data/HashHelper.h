//
// Created by Skrepy on 2026/1/6.
//
#pragma once
#include <iostream>

class HashHelper {
private:
    HashHelper() = default;

public:
    static size_t getHash(std::string str);
    static std::string getCurrentTimestamp();
    static std::string getHashFromCurrentTime();
    static std::string simpleHashString(const std::string &input);
};
