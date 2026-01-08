#include "../../header/screen/Option.h"
#include <functional>
#include <iostream>
#include <utility>
#include "../../header/data/info/Text.h"

Option::Option() = default;

Option::Option(const Text &content, std::string colorCode, std::function<void()> selectedFunction) :
    content(std::move(content)), colorCode(std::move(colorCode)),
    selectedFunction(std::move(selectedFunction)) // 移动以提高效率
{}

Text Option::getContent() { return this->content; }

std::string Option::getColorCode() { return this->colorCode; }

std::function<void()> Option::getSelectedFunction() { return this->selectedFunction; }

void Option::setContent(const Text &content) { this->content = content; }

void Option::setColorCode(std::string colorCode) { this->colorCode = std::move(colorCode); }

void Option::setSelectedFunction(std::function<void()> selectedFunction) {
    this->selectedFunction = std::move(selectedFunction);
}

// 新增方法：执行选中的函数
void Option::executeSelectedFunction() const {
    if (selectedFunction) {
        selectedFunction();
    }
}
