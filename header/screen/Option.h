#pragma once
#include <functional>
#include <iostream>
#include <string>
#include "../../header/data/info/Text.h"
#include "../../header/screen/Option.h"

class Option {
private:
    Text content; // 选项内容
    std::string colorCode; // 被选中时的颜色的代码
    std::function<void()> selectedFunction; // 支持带参数的函数对象
public:
    Option();
    ~Option() = default;
    explicit Option(const Text &content, std::string colorCode = "", std::function<void()> selectedFunction = nullptr);
    Text getContent(); // 获取选项内容
    std::string getColorCode(); // 获取颜色代码
    std::function<void()> getSelectedFunction(); // 获取函数对象
    void setContent(const Text &content); // 设置选项内容
    void setColorCode(std::string colorCode); // 设置颜色代码
    void setSelectedFunction(std::function<void()> selectedFunction); // 设置函数对象

    // 新增方法：执行选中的函数
    void executeSelectedFunction() const;
};
