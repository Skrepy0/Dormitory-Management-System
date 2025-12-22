#pragma once
#include "../../header/menu/Option.h"
#include"../../header/data/info/Text.h"
#include<iostream>
typedef void (*Func)();
class Option {
private:
	Text content;// 选项内容
	std::string colorCode;// 被选中时的颜色的代码
	Func selectedFunction{};// 执行的函数指针
public:
	Option();
	explicit Option(const Text& content,std::string colorCode = "", Func selectedFunction = nullptr);
	Text getContent();// 获取选项内容
	std::string getColorCode();// 获取颜色代码
	Func getSelectedFunction();// 获取函数指针
	void setContent(const Text& content);// 设置选项内容
	void setColorCode(std::string colorCode);// 设置颜色代码
	void setSelectedFunction(Func selectedFunction);// 设置函数指针
};