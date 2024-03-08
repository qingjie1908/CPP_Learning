#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>

using std::string;
using std::vector;

using std::cin;
using std::cout;
using std::endl;

void f()
{
    cout << "call f()" << endl;
}
void f(int)
{
    cout << "call f(int)" << endl;
}
void f(int, int)
{
    cout << "call f(int, int)" << endl;
}
void f(double, double = 3.14)
{
    cout << "call f(double, double = 3.14)" << endl;
}

int main()
{
    // f(2.56, 42); // call f(double, double) or f(int, int), ambiguous, error
    f(42); // call f(int)
    f(42, 0); // call f(int, int)
    f(2.56, 3.14); // call f(double, double)
    // return 0;
}