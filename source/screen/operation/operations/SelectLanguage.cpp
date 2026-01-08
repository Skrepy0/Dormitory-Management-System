//
// Created by Skrepy on 2026/1/2.
//

#include "../../../../header/screen/operation/operations/SelectLanguage.h"

#include "../../../../header/data/DataHelper.h"

void setLanguage(std::string value) { Text::setLanguage(value); }

std::vector<Option> SelectLanguage::init() {
    std::vector<Option> options;
    auto fileList = DataHelper::getFileListInDirectory(R"(..\data\lang)");
    for (auto &file: fileList) {
        if (file == "language.json")
            continue;
        file = file.substr(0, file.find_last_of("."));
        options.emplace_back(Option(Text::of(DataHelper::getLanguageList()[file]).append(Text::of("\n$r")), "a",
                                    [file]() -> void { setLanguage(file); }));
    }
    return options;
}

SelectLanguage::SelectLanguage() : SelectMenu(Text("operation.select_language.title"), init(), "a", 8) {}

void SelectLanguage::loop() { SelectMenu::mainLoop(); }
