#include <iostream>
#include <string>
#include <vector>

class NoDefault{
// friend class C;
public:
    NoDefault(int i){}
};

class C{
public:
    C():item1(2){}
    NoDefault item1; // item1 has no default constructor in class NoDefault, so need add default constructor C() and intialize item1(a int number)
};

int main()
{
    std::vector<C> vec(10);
    return 0;
}