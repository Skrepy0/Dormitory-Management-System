#include<iostream>
#include<vector>
#include"./header/data/info/Text.h"
#include"./header/data/Accommodations.h"
#include"./header/data/BuildingData.h"
#include"./header/data/UserData.h"
#include "header/data/StayLog.h"
#include "header/data/info/Message.h"
#include "header/screen/SelectMenu.h"
#include <windows.h>
#include"./header/screen/Options.h"


int main() {
    Message message(Text::of("\n✅ "));
    message.printContent();
    BaseOptions b;
    b.showTitle("$c宿舍管理系统$r");
    system("pause");
}
