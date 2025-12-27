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

#include "header/screen/operation/UserOperationMenu.h"


int main() {

    UserOperationMenu user_operation_menu;
    user_operation_menu.loop();
}
