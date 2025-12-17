#include<iostream>
#include <utility>
#include"../../header/menu/Menu.h"
#include"../../header/menu/MenuHelper.h"

void Menu::addSelfToMenuList() const {
	// MenuHelper::menuList.push_back(*this);
}

Menu::Menu()
= default;

Menu::Menu(std::vector<Option> optionList):optionList(std::move(optionList)) {// 移动向量提高效率
}

void Menu::init() {
}


void Menu::display()
{
	}

void Menu::remountToParentMenu()
{
	}

void Menu::mountToChildMenu()
{
	}


