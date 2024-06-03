#include <vector>
#include <string>

int f(){
    int a = 3;
    return a;
}

struct my_X{
    int a;
    std::string b;
};

my_X g1(){
    my_X obj;
    return obj;
}

my_X& g2(my_X orig){
    my_X obj;
    return obj;
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

    //return type is non-reference return rvalue
    //my_X& my_l_ref = g1(); //error
    my_X&& my_r_ref = g1();

    my_X obj; //obj is lvalue
    //g2 return reference type, whihc is lvalue
    my_X& my_l_ref = g2(obj);
    //my_X&& my_r_ref2 = g2(obj); //error

}