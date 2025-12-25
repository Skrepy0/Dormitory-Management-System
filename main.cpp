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


int main() {
    Message message(Text::of("123"));
    message.printContent();
    system("pause");
}
