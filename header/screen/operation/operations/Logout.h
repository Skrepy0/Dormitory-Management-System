#pragma once
#include <conio.h>
#include <string>
// Logout.h
class Logout {
public:
    static bool checkEscKey();

private:
    static int getSingleKeyNonBlock();
};
