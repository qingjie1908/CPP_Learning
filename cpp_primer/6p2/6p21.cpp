#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int fact(int x)
{
    int result = 1;
    while (x > 1) {
        result *= x--;
    }
    return result;
}

void reset(int *ip)
{
    *ip = 0;
    ip = 0; // local ip now is a null pointer
}

void swapint(int *i, int *j)
{
    int x = *i; //intermediate value x to store value in which i point to;
    *i = *j; // object j point to assign to oject i point to
    *j = x;
}

bool isshorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

bool isshorter2(const string s1, string s2)
{
    return s1.size() < s2.size();
}

int main()
{
    int x = 3;
    cout << fact(x) << endl;
    cout << x << endl;

    int ip = 5;
    cout << ip << " " << &ip << endl;
    reset(&ip);
    cout << ip << " " << &ip << endl; // &ip not change

    cout << endl << "==== Ex 6.10 ====" << endl;
    int i = 15, j = 20;
    cout << "i is : " << i << ", j is : " << j << endl;
    cout << "swap i and j" << endl;
    swapint(&i, &j);
    cout << "Now i is : " << i << ", j is : " << j << endl;

    string s1;
    cin >> s1;
    string s2;
    cin >> s2;
    cout << isshorter(s1, s2) << endl;
    cout << isshorter2(s1, s2) << endl;
    s1 += s2;
    cout << isshorter(s1, s2) << endl;

}