#include "../../../header/data/info/Message.h"
#include<unordered_map>
#ifdef _WIN32
#include <windows.h>
void enableWindowsAnsiSupport() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif
Message::Message(Text text):text(text)
{
    Text t("@c红 @a绿 @d浅紫色 @b天蓝色@r");
    this->target = t.getContent();
}

const std::unordered_map<char,std::string> COLOR_MAP = {
     {'c',"\033[31m"}, //@c -> 红色
    {'a', "\033[32m"},  // @a → 绿色
    {'d',"\033[35m"}, //@d -> 紫色（浅紫）
    {'b',"\033[34m"}, //@b -> 蓝色（天蓝）
    {'r',"\033[0m"} //@r -> 恢复默认
};
void Message::printContent()
{
#ifdef _WIN32
    enableWindowsAnsiSupport();
#endif
    for (size_t i = 0; i < target.size(); ) {
        if (static_cast<unsigned char>(target[i]) == static_cast<unsigned char>('@')  && (i + 1) < target.size()) {
            char colorCode = target[i + 1];
            auto it = COLOR_MAP.find(colorCode);

            if (it != COLOR_MAP.end()) {
                std::cout << it->second;
            }
            i += 2;
        } else {
            std::cout << target[i];
            i++;
        }
    }
    std::cout << COLOR_MAP.at('r') << std::endl;
}