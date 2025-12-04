#pragma once
#include<iostream>
#include"Menu.h"

class MenuHelper {// 工具类
private:
	MenuHelper() {};
public:
	static std::vector<Menu> menuList;
	static void clearScreen();// 清屏函数
};
