#pragma once
#include <iostream>
#include <vector>
#include "../../data/info/Text.h"
#include "../../../header/menu/AbstractMenu.h"
typedef void (*Func)();
class Select {
private:
	std::vector<Text> options;
	bool multipleSelection = false;
	std::vector<int> selectedIndices;
	std::vector<std::pair<Text, bool>> optionStatusList;// 选项及其选中状态的列表
	bool isRunning = true;
	int indexPointer = 0;// 选择指针位置
	void init();
	void deleteSelectedPointer(int index);
	Func functionAfterSelection;// 选择后执行的函数指针默认是nullptr（回车键）
	Func functionQuitSelection;// 退出选择时执行的函数指针默认是nullptr(按Esc)
public:
	Select(std::vector<Text> optionsList, bool multipleSelection,Func functionAfterSelection = nullptr,Func functionQuitSelection = nullptr);
	void loop();// 进入选择循环
	void updateOptions();
	void onSelection(int index);
	void updatePointer(int direction);// 选择器上下移动与选项颜色更新
	void monitorKeyEvent();// 监视输入
	void quitSelection();// 退出选择
	std::vector<std::pair<Text, bool>> getOptionStatusList();// 获取选项状态列表
};
