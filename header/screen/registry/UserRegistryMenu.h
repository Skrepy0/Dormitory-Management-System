#pragma once
#include"../SelectMenu.h"
class UserRegistryMenu:public SelectMenu {
public:
    UserRegistryMenu(Text title) : SelectMenu(title, {
        Option(Text("test.option.1"), "a", nullptr),
        Option(Text("test.option.2"), "b", nullptr),
        Option(Text("test.option.3"), "c", nullptr),
        Option(Text("test.option.4"), "d", []()-> void {

        })
    }) {
    }

    void mainLoop() {
        SelectMenu::mainLoop();
    }
};
