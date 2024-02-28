#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

void reset(int &i)
{
    i = 0;
}

void swapint(int &i, int &j)
{
    int x = i;
    i = j;
    j = x;
}

void f(int)
{
    int x = 1;
}

void f1(int&)
{
    int y = 1;
}


int main()
{
    cout << endl << "==== Ex 6.11 ====" << endl;
    int x = 3;
    cout << "Original x is: " << x << endl;
    reset(x);
    cout << "Reset x is: " << x << endl;

    cout << endl << "==== Ex 6.12 ====" << endl;
    int m = 11, n = 12;
    cout << "Original m and n are: " << m << " and " << n << endl;
    swapint(m, n);
    cout << "After swap, m and n are: " << m << " and " << n << endl;

    int &m_r = m;
    f(m);
    f1(m_r);

}