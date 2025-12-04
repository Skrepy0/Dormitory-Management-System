#pragma once
#include "../../header/menu/Option.h"
class AbstractMenu {
protected:
	std::string id;// 菜单的唯一标识符
	std::vector<Option> options;// 菜单选项列表
public:
	virtual void init() = 0;// 菜单初始化函数
	virtual void display() = 0;// 菜单显示函数(循环)
	virtual void remountToParentMenu() = 0;// 返回父菜单
	virtual void mountToChildMenu() = 0;// 进入子菜单
};