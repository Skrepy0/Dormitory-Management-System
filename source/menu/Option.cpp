#include "../../header/menu/Option.h"
#include"../../header/data/info/Text.h"
#include<iostream>
#include <utility>
Option::Option()= default;

Option::Option(const Text& content, std::string colorCode
	, Func selectedFunction) : content(content),
colorCode(std::move(colorCode)), selectedFunction(selectedFunction)// 移动以提高效率
{}

Text Option::getContent() {
	return this->content;
}
std::string Option::getColorCode() {
	return this->colorCode;
}
Func Option::getSelectedFunction() {
	return this->selectedFunction;
}
void Option::setContent(const Text& content) {
	this->content = content;
}
void Option::setColorCode(std::string colorCode) {
	this->colorCode = std::move(colorCode);
}
void Option::setSelectedFunction(Func selectedFunction) {
	this->selectedFunction = selectedFunction;
}

