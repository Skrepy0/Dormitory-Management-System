#pragma once
#include"../Menu.h"
class UserRegistryMenu:public Menu {
public:
    UserRegistryMenu(Text title) : Menu(title, {
        Option(Text("test.option.1"), "a", nullptr),
        Option(Text("test.option.2"), "b", nullptr),
        Option(Text("test.option.3"), "c", nullptr),
        Option(Text("test.option.4"), "d", []()-> void {

        })
    }) {
    }

    void mainLoop() {
        Menu::mainLoop();
    }
};
