#include <iostream>

int main()
{
    // const int ci = 0, &cj = ci;
    // decltype(ci) x = 0;
    // decltype(cj) y = x;
    // // y = 1; error, y is const int&

    // ==================
    // int a = 3, b = 4;
    // decltype(a) c = a;
    // std::cout << "c is " << c << std::endl; //c is int, initialzied to 3

    // decltype((b)) d = a; // d is a reference to int and bound to a
    // std::cout <<  "d is " << d << std::endl;

    // ++c;
    // std::cout << "new c is " << c << std::endl; //4
    // std::cout << "a is " << a << std::endl; //3

    // ++d;
    // std::cout << "d is " << d << std::endl; //4
    // std::cout << "new a is" << a << std::endl; //4

    // ==================
    int a = 3, b = 4;
    decltype(a) c = a; // c is int, initialized with 3
    decltype(a = b) d = a; // d is refence to int, and bound to a

    const int e = 5, &f = e;
    std::cout << "e address is, f address is " << &e << " " << &f << std::endl; //0x000, 0x000
    auto g1 = e; // g1 is a int and initialzied to 5, top level const dropped
    std::cout << "g1 address is and value is " << &g1 << " " << g1 << std::endl; //0x111, 5
    auto g2 = f; // g2 is a int and intiazilded to 5, top level const dropped
    std::cout << "g2 address is and value is " << &g2 << " " << g2 << std::endl; //0x222, 5
    auto &g3 = e; // g3 is a reference to const int, bound to e
    std::cout << "g3 address is and value is " << &g3 << " " << g3 << std::endl; //0x000, 5
    auto &g4 = f; // g4 is a reference to const int, bound to e
    std::cout << "g4 address is and value is " << &g4 << " " << g4 << std::endl; //0x000, 5

    decltype(e) g5 = 1;
    decltype((e)) g6 = 2;
    // g6 = 2; // error, g6 const int &, read only
    decltype(f) g7 = f;
    std::cout << "g7 address is and value is " << &g7 << " " << g7 << std::endl; //0x000, 5
    decltype(f+1) g8 = e;
 
    return 0;

}