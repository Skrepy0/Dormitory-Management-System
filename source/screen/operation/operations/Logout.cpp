#include "../../../../header/screen/operation/operations/Logout.h"
#ifdef _WIN32
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

int Logout::getSingleKeyNonBlock()
{
#ifdef _WIN32

    if (_kbhit())
    {
        return _getch();
    }
    else
    {
        return -1;
    }
#else
    struct termios oldAttr;
    tcgetattr(STDIN_FILENO, &oldAttr);

    struct termios newAttr = oldAttr;
    newAttr.c_lflag &= ~(ICANON | ECHO);
    newAttr.c_cc[VMIN] = 0; // 最少读取0个字符（无按键也返回）
    newAttr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newAttr);

    int oldFlags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldFlags | O_NONBLOCK);

    int ch = getchar(); // 无按键时返回-1

    // 恢复终端属性
    tcsetattr(STDIN_FILENO, TCSANOW, &oldAttr);
    fcntl(STDIN_FILENO, F_SETFL, oldFlags);

    return (ch == EOF) ? -1 : ch;
#endif
}


bool Logout::checkEscKey()
{
    int key = getSingleKeyNonBlock();
    return (key == 27);
}
