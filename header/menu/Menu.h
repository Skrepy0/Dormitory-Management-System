#pragma once
#include<iostream>
#include<vector>
#include "Option.h"
class Menu {
protected:
	std::vector<Option> optionList;
	void addSelfToMenuList() const;// 将自身添加到菜单列表中
public:
	virtual ~Menu() = default;
	Menu();
	explicit Menu(std::vector<Option> optionList);
	virtual void init() ;// 菜单初始化函数
	virtual void display() ;// 菜单显示函数(循环)
	virtual void remountToParentMenu() ;// 返回父菜单
	virtual void mountToChildMenu() ;// 进入子菜单
};
