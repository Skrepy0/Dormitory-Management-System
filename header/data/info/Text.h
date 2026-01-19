#pragma once
#include <iostream>
#include "../../../source/data/library/json.hpp"

class Text {
    friend std::ostream &operator<<(std::ostream &out, Text &text);

private:
    std::string path; // json键（需要转化）
    std::string content; // 内容（显示出来的内容）
    std::string language; // 语言
    void init();

    void translate(); // 将path转化成content// to do
    static bool writeLanguageToFile(const std::string &lang);

    nlohmann::json readFromJson();

public:
    Text();

    Text(std::string path);

    static Text of(std::string content); // 不通过json直接显示content内容
    std::string getPath(); // 获取path
    std::string getContent(); // 获取content
    void setPath(std::string path); // 设置path的值
    void setContent(std::string content); // 设置content的值
    static void setLanguage(std::string lang); // 设置语言，lang的值可为"en_us"（英语）、"zh_cn"(中文)
    void addColorCode(std::string colorCode); // 为content添加颜色代码
    Text operator+(Text other); // 重载+运算符，连接两个Text对象的content
    Text &operator=(const Text &other);

    void eraseChar(int index); // 删除content中指定位置的字符
    void eraseChar(int begin, int end); // 删除content中指定范围的字符
    void replaceChar(int index, char c); // 替换content中指定位置的字符

    Text append(Text text);

    static Text intToText(int num);
};
