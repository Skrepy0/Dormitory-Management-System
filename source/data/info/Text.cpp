#include "../../../header/data/info/Text.h"
#include <cstring>
#include <direct.h>
#include <fstream>
#include <iostream>
#include "../../../header/data/Accommodations.h"

// 使用项目内固定的资源目录（相对于项目根目录/工作目录）
namespace {
    std::string LAN_PATH;
    std::string FILE_PATH;
} // namespace

void Text::init() {
    char cwd[1024];
    if (_getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::string frontPath = cwd;
        frontPath.erase(frontPath.size() - 17, 18);
        // 获取当前工作目录成功
        LAN_PATH = frontPath + "data\\lang\\";
        FILE_PATH = frontPath + "data\\lang\\language.json";
    } else {
        std::cout << "Error: Could not get current working directory" << std::endl;
    }
    try {
        std::ifstream in_file(FILE_PATH);
        if (!in_file.is_open()) {
            language = "en_us"; // 默认英语
            return;
        }
        nlohmann::json langData;
        in_file >> langData;
        if (langData.contains("current") && langData["current"].is_string()) {
            language = (std::string) (langData["current"]);
        } else {
            language = "en_us";
        }
        in_file.close();
    } catch (...) {
        language = "en_us"; // 默认英语
    }
}

void Text::setContent(std::string content) { this->content = content; }

void Text::setLanguage(std::string lang) {
    if (!writeLanguageToFile(lang)) {
        std::cout << "Error: Could not set language";
    }
}

void Text::addColorCode(std::string colorCode) { content = colorCode + content; }

Text Text::operator+(Text other) {
    Text result;
    result.setContent(this->getContent() + other.getContent());
    return result;
}

Text &Text::operator=(const Text &other) {
    if (this == &other) {
        return *this;
    }
    this->path = other.path;
    this->content = other.content;
    this->language = other.language;
    return *this;
}

void Text::eraseChar(int index) {
    if (index < 0 || index >= content.size()) {
        return;
    }
    content.erase(index, 1);
}

void Text::eraseChar(int begin, int end) {
    std::string res;
    for (int i = 0; i < content.size(); i++) {
        if (i < begin || i > end) {
            res += content[i];
        }
    }
    content = res;
}

void Text::replaceChar(int index, char c) { content[index] = c; }

void Text::translate() {
    auto data = readFromJson();
    if (!path.empty() && data.contains(path)) {
        content = (std::string) (data[path]);
    } else {
        content = path;
    }
}

bool Text::writeLanguageToFile(const std::string &lang) {
    // 先读取当前文件内容（如果存在），再修改并写回
    std::ifstream in_file(FILE_PATH);
    nlohmann::json langData;
    if (in_file.is_open()) {
        try {
            in_file >> langData;
        } catch (...) {
            langData = nlohmann::json::object();
        }
        in_file.close();
    } else {
        // 如果无法打开现有语言文件，先创建一个基础对象
        langData = nlohmann::json::object();
    }

    std::ofstream out_file(FILE_PATH);
    if (!out_file.is_open()) {
        return false;
    }
    langData["current"] = lang;
    out_file << langData.dump(4);
    out_file.close();
    return true;
}

nlohmann::json Text::readFromJson() {
    std::string langFilePath = LAN_PATH + language + ".json";
    std::ifstream in_file(langFilePath);
    nlohmann::json langData;
    if (!in_file.is_open()) {
        // 无法打开语言文件，返回空对象
        return nlohmann::json::object();
    }
    try {
        in_file >> langData;
    } catch (...) {
        // 返回空对象以避免抛出
        in_file.close();
        return nlohmann::json::object();
    }
    in_file.close();
    return langData;
}

Text::Text() { init(); }

Text::Text(std::string path) {
    init();
    this->path = path;
    if (!path.empty()) {
        translate(); // 转换path到value
    } else {
        this->content = "";
    }
}

Text Text::of(std::string text) {
    Text t("");
    t.setContent(text);
    return t;
}

std::string Text::getPath() { return this->path; }

std::string Text::getContent() {
    if (!path.empty()) {
        init();
        translate();
    }
    return this->content;
}

void Text::setPath(std::string path) {
    this->path = path;
    translate();
}

std::ostream &operator<<(std::ostream &out, Text &text) {
    out << text.getContent();
    return out;
}
