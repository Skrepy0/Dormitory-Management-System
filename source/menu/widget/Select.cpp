#include "../../../header/menu/widget/Select.h"
#include "../../../header/menu/MenuHelper.h"
#include <conio.h>
#include <algorithm>
#include <iostream>
const int rightArrowIndex = 0;
const int pageBreakIndex = 4;
const int colorCodeIndex = 5;
const int selectedSymbolIndex = 2;
const char selectedSymbol = '*';
const char colorCode = 'a';
Select::Select(std::vector<Text> optionsList, bool multipleSelection,Func functionAfterSelection,Func functionQuitSelection) : options(optionsList), multipleSelection(multipleSelection),functionAfterSelection(functionAfterSelection),functionQuitSelection(functionQuitSelection) {
	init();
}
void Select::init() {
	for (auto & option : options) {
		optionStatusList.push_back(std::make_pair(Text::of(" ( )  ")+option, false));// 初始状态均为未选中
	}
	optionStatusList[0].second = true; // 默认第一个选项为指针位置
	optionStatusList[0].first.replaceChar(rightArrowIndex,'>');
	optionStatusList[0].first.replaceChar(pageBreakIndex,'§');
	optionStatusList[0].first.replaceChar(colorCodeIndex,colorCode);
	// ">(*)§aOption"
}
void Select::deleteSelectedPointer(int index) {
	Text selectedOption = optionStatusList[index].first = optionStatusList[index].first;
	selectedOption.replaceChar(rightArrowIndex, ' ');
	selectedOption.replaceChar(pageBreakIndex, ' ');
	selectedOption.replaceChar(colorCodeIndex, ' ');
	optionStatusList[index].first = selectedOption;

}
void Select::loop() {
	while(isRunning) {
		updateOptions();
		// 监视输入并处理
		monitorKeyEvent();	
	}
}

void Select::updateOptions() {
	MenuHelper::clearScreen();
	for (auto i: optionStatusList) {
		Text optionText = i.first;
		std::cout << optionText.getContent() << std::endl;
	}
}

void Select::onSelection(int index) {
	if (!multipleSelection) {
		// 单选模式下，清除其他选项的选中状态
		for (auto& optionStatus : optionStatusList) {
			if (optionStatus.second) {
				optionStatus.second = false;
				Text selectedOption = optionStatus.first;
				selectedOption.replaceChar(selectedSymbolIndex, ' ');
				optionStatus.first = selectedOption;
			}
		}
		optionStatusList[index].second = true;
		Text selectedOption = optionStatusList[index].first;
		selectedOption.replaceChar(selectedSymbolIndex, selectedSymbol);
		optionStatusList[index].first = selectedOption;
		selectedIndices.clear();
		selectedIndices.push_back(index);
		return;
	}
	if (optionStatusList[index].second) {
		optionStatusList[index].second = false;
		selectedIndices.erase(std::remove(selectedIndices.begin(), selectedIndices.end(), index), selectedIndices.end());
		Text selectedOption = optionStatusList[index].first;
		selectedOption.replaceChar(selectedSymbolIndex, ' ');
		optionStatusList[index].first = selectedOption;
	}
	else {
		optionStatusList[index].second = true;
		selectedIndices.push_back(index);
		Text selectedOption = optionStatusList[index].first;
		selectedOption.replaceChar(selectedSymbolIndex, selectedSymbol);
		optionStatusList[index].first = selectedOption;
	}
}

void Select::updatePointer(int direction) {
	int index = indexPointer + direction;
	if (index < 0) {
		indexPointer = options.size() - 1;
	}
	else if (index >= options.size()) {
		indexPointer = 0;
	}
	else {
		indexPointer = index;
	}
	Text selectedOption = optionStatusList[indexPointer].first;
	selectedOption.replaceChar(rightArrowIndex, '>');
	selectedOption.replaceChar(pageBreakIndex, '§');
	selectedOption.replaceChar(colorCodeIndex, colorCode);
	optionStatusList[indexPointer].first = selectedOption;

}

void Select::monitorKeyEvent() {
	int key = _getch();
	switch (key)
	{
	case 72: // 上箭头
		deleteSelectedPointer(indexPointer);
		updatePointer(-1);
		break;
	case 80: // 下箭头
		deleteSelectedPointer(indexPointer);
		updatePointer(1);
		break;
	case 13: // 回车键
		// 确认选择: 若为单选模式，确保当前指针为选中项；然后执行回调并退出
		if (!multipleSelection) {
			onSelection(indexPointer);
		}
		if (functionAfterSelection) {
			functionAfterSelection();
		}
		quitSelection();
		break;
	case 27: // ESC键
		quitSelection();
		if (functionQuitSelection) {
			functionQuitSelection();
		}
		break;
	case 32: // 空格键
		onSelection(indexPointer);
		break;
	default:
		break;
	}
}

void Select::quitSelection() {
	isRunning = false;
}

std::vector<std::pair<Text, bool>> Select::getOptionStatusList() {
	return optionStatusList;
}
