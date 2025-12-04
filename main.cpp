#include<iostream>
#include<vector>
#include"./header/menu/widget/Select.h"
#include"./header/data/info/Text.h"
#include"./header/menu/Menu.h"
#include"./header/data/Accommodations.h"
#include"./header/data/BuildingData.h"
#include"./header/data/UserData.h"

int main() {
    UserData user("123","10","123456","123@qq.com","1","4","4");
    std::cout << user.getData() << std::endl;
    user.writeToFile();
}