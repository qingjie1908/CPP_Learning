#include <vector>

int f(){
    int a = 3;
    return a;
}


int main()
{
    int &&r_ref = f();
    const int &l_ref = f();
    const int &&r_ref2 = f();
    //int &l_ref2 = f(); //error, f() return rvalue

    std::vector<int> vi(100);
    std::vector<int>& l_ref = vi;
    //std::vector<int>&& r_ref = vi; //error, vi is lvalue
    const std::vector<int>& l_ref2 = vi;
    //const std::vector<int>&& r_ref2 = vi; //error, vi is lvalue

    int&& r1 = f();
    int& r3 = r1;
    int&& r4 = vi[0]*f();
}