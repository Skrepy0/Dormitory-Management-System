#include<iostream>
#include<vector>
#include"./header/menu/widget/Select.h"
#include"./header/data/info/Text.h"
#include"./header/menu/Menu.h"
#include"./header/data/Accommodations.h"
#include"./header/data/BuildingData.h"
#include"./header/data/UserData.h"
#include "header/data/info/Message.h"

int main() {
    Message message(Text::of("@a1231456"));
    message.printContent();
}
