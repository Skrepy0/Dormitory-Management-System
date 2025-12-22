#include "../../../header/data/info/Message.h"
#include<unordered_map>
#ifdef _WIN32
#include <windows.h>

void enableWindowsAnsiSupport()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#endif
Text Message::getText() const
{
    return text;
}

void Message::setText(Text text)
{
    this->text = text;
    this->target = text.getContent();
}

Message::Message(Text text) : text(text)
{
    this->target = text.getContent();
}


void Message::printContent()
{
    SetConsoleOutputCP(CP_UTF8);
#ifdef _WIN32
    enableWindowsAnsiSupport();
#endif
    for (int i = 0; i < target.size();)
    {
        if (target[i] == '\\' && (i + 1) < target.size() && target[i + 1] == '$')
        {
            std::cout << '$'; // 转义后只输出$
            i += 2; // 跳过\和$两个字符
        }
        // 2. 处理原有的$+颜色码逻辑（如$r/$g等）
        else if (target[i] == '$' && (i + 1) < target.size())
        {
            char colorCode = target[i + 1];
            auto it = COLOR_MAP.find(colorCode);
            if (it != COLOR_MAP.end())
            {
                std::cout << it->second; // 输出颜色控制符
            }
            else
            {
                // 非合法颜色码：原样输出$+后续字符（比如$x）
                std::cout << target[i] << target[i + 1];
            }
            i += 2; // 跳过$和颜色码
        }
        // 3. 普通字符（包括单独的\、单独的$、其他字符）
        else
        {
            std::cout << target[i];
            i++;
        }
    }
}
