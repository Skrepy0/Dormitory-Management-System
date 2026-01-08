/**
 * @file HashHelper.h
 * @brief 哈希辅助工具类，提供字符串哈希和时间戳相关功能
 * @details 该类包含各种哈希函数和时间戳生成方法，用于生成唯一标识符
 * @author Skrepy
 * @date 2026/1/6
 */

#pragma once
#include <iostream>

/**
 * @class HashHelper
 * @brief 哈希辅助工具类
 * @details 提供静态方法用于生成哈希值、获取当前时间戳以及生成基于时间的哈希值
 */
class HashHelper {
private:
    /**
     * @brief 私有默认构造函数
     * @details 该类为工具类，不需要实例化，因此将构造函数设为私有
     */
    HashHelper() = default;

public:
    /**
     * @brief 获取字符串的哈希值
     * @param str 需要计算哈希值的字符串
     * @return 返回字符串的哈希值
     * @details 使用标准哈希算法计算字符串的哈希值
     */
    static size_t getHash(std::string str);

    /**
     * @brief 获取当前时间戳
     * @return 返回格式化的当前时间戳字符串
     * @details 时间戳格式为年-月-日 时:分:秒
     */
    static std::string getCurrentTimestamp();

    /**
     * @brief 基于当前时间生成哈希值
     * @return 返回基于当前时间生成的哈希字符串
     * @details 结合当前时间戳和随机数生成唯一哈希值
     */
    static std::string getHashFromCurrentTime();

    /**
     * @brief 简单字符串哈希函数
     * @param input 需要哈希的输入字符串
     * @return 返回计算后的哈希字符串
     * @details 使用简单的哈希算法计算字符串哈希值，适用于快速生成标识符
     */
    static std::string simpleHashString(const std::string &input);
};
