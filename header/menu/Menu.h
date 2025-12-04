#pragma once
#include<iostream>
#include<vector>
#include"../../header/menu/AbstractMenu.h"
class Menu:public AbstractMenu {
protected:
	void addSelfToMenuList() const;// 将自身添加到菜单列表中
public:
	Menu();
	void init() override;// 菜单初始化函数
	void display() override;// 菜单显示函数(循环)
	void remountToParentMenu() override;// 返回父菜单
	void mountToChildMenu() override;// 进入子菜单

};
