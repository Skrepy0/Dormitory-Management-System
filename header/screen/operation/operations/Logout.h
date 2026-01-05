#pragma once
#include <string>
#include <conio.h>
// Logout.h
class Logout {
public:
    static bool checkEscKey();

private:
    static int getSingleKeyNonBlock();
};
