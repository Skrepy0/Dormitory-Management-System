#include "../../header/menu/Option.h"
#include"../../header/data/info/Text.h"
#include<iostream>
Option::Option() :content(Text::of("")), colorCode(""), selectedFunction(nullptr) {}

Option::Option(Text content, std::string colorCode, Func selectedFunction) : content(content), colorCode(colorCode), selectedFunction(selectedFunction) {}

Text Option::getContent() {
	return this->content;
}
std::string Option::getColorCode() {
	return this->colorCode;
}
Func Option::getSelectedFunction() {
	return this->selectedFunction;
}
void Option::setContent(Text content) {
	this->content = content;
}
void Option::setColorCode(std::string colorCode) {
	this->colorCode = colorCode;
}
void Option::setSelectedFunction(Func selectedFunction) {
	this->selectedFunction = selectedFunction;
}

