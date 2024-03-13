#include <iostream>
#include <string>
#include <vector>
#include "Screen.h"

int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    return 0;
}

// ======== Ex 7.31 ========
/*
class Y;
class X
{
    Y *p1;  // must have declaration of class Y first
};

class Y
{
    X obj1;
};
*/