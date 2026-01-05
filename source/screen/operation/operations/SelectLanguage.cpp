//
// Created by Skrepy on 2026/1/2.
//

#include "../../../../header/screen/operation/operations/SelectLanguage.h"

void setLanguageZHCN() { Text::setLanguage("zh_cn"); }

void setLanguageENUS() { Text::setLanguage("en_us"); }

SelectLanguage::SelectLanguage() :
    SelectMenu(Text("operation.select_language.title"),
               {Option(Text("operation.select_language.option.en_us"), "y", setLanguageENUS),
                Option(Text("operation.select_language.option.zh_cn"), "p", setLanguageZHCN)},
               "a", 6) {}

void SelectLanguage::loop() { SelectMenu::mainLoop(); }
