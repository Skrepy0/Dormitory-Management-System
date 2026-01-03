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
#include"./header/screen/InputMenu.h"
#include "header/screen/operation/operations/user/UserApplication.h"
#include"./header/screen/operation/operations/ChangePassword.h"
#include "header/screen/operation/operations/user/UserMaintenance.h"



int main() {
    Message(Text::of("$mred$r\n")).printContent();
    Message(Text::of("$kred$r\n")).printContent();
    Message(Text::of("$Ared$r\n")).printContent();
    Message(Text::of("$Bred$r\n")).printContent();
    Message(Text::of("$Cred$r\n")).printContent();
    Message(Text::of("$Dred$r\n")).printContent();
    Message(Text::of("$Fred$r\n")).printContent();
    Message(Text::of("$Gred$r\n")).printContent();
    Message(Text::of("$Hred$r\n")).printContent();
    Message(Text::of("$Ired$r\n")).printContent();
    system("pause");

}
