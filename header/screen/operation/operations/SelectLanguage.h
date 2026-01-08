#pragma once
#include "../../SelectMenu.h"

class SelectLanguage : public SelectMenu {
private:
    static std::vector<Option> init();

public:
    SelectLanguage();
    void loop();
};
