//
// Created by Skrepy on 2026/1/2.
//

#include "../../../../header/screen/operation/operations/SelectLanguage.h"

SelectLanguage::SelectLanguage():SelectMenu(Text("operation.select_language.title"),{
    Option(Text("operation.select_language.option.en_us"),"y"),
    Option(Text("operation.select_language.option.zh_cn"),"p")
},"a",5) {
}

void SelectLanguage::loop() {
    SelectMenu::mainLoop();
}
