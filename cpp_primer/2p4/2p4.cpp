#include <iostream>


int main()
{
    // int i = 0;
    // int *constp1 = &i; //
    // const int ci = 42; //
    // const int *p2 = &ci;//
    // const int *const p3 = p2; // right-most const is top-level, left-most is not const int &r = ci; // const in reference types is always low-level

    //=================== 
    // int ival = 1024;
    // int *pi = &ival;
    // std::cout << pi << " " << *pi << std::endl;

    // int **ppi = &pi;
    // std::cout << ppi << " " << *ppi << " " << **ppi << std::endl;

    //=================== 
    // int i = -1;
    // const int i2 = i, &r = i;
    // const double pi = 3.14;
    // const double *p = &pi;
    // double dval = 4;
    // p = &dval;

    // int i = -1, y = 10;
    // const int *p = &i;
    // *p = -1;
    // p = &y;

    // int i = -1, y = -10;
    // const int *p = &i;
    // p = &y;
    // y = 1;
    // double x = 0.3;
    // p = &x;

    // int i = 2;
    // double v3 = 0.123;
    // const int v2 = 0;
    // int v1 = v2;
    // int *p1 = &v1, &r1 = v1;
    // const int *p2 = &v2, *const p3 = &i, &r2 = v2;
    // r1 = v2;
    // p1 = p2;
    // p2 = p1;
    // *p1 = 1;
    // p1 = p3;
    // p3 = p1;
    // p2 = p3;

    // const int null = 0;
    // constexpr int i = 0;
    // int *p = null;

    // const int i = 1;
    // auto *p = &i;

    // double b = 3;
    // const int &a = b;

    // ===================exercise 2.5.2
    int i = 20,  &r = i;
    auto a  = r; // a is int
    std::cout << "a is " << a << std::endl; //20
    
    const int ci = i, &cr =  ci;
    auto b = ci; // b is int
    std::cout << "b is " << b << std::endl; //20

    auto c = cr; // c is int
    std::cout << "c is " << c << std::endl; //20

    auto d = &i; // d is a pointer to int i, int *;
    std::cout << "d address is and point to " << d << " " << *d << std::endl; //x1111 20

    auto e = &ci; // e is a pointer to const int ci, const int *
    // *e = 1; error since *e is read only const int
    std::cout << "e address is and point to " << e << " " << *e << std::endl; //x2222 20

    auto y = &cr; // y is a pointer to const int ci, const int *
    std::cout << "y address is and point to " << y << " " << *y << std::endl; //x2222 20
    // *y = 1; errpr, pointer to const int, de-reference value is read only

    const auto x = &cr; //x is a const pointer to const int ci, const int *const
    std::cout << "x address is and point to " << x << " " << *x << std::endl; //x2222 20

    const auto f  = ci; // f is const int
    // f = 2; error, f cannot be assigned, read only const int
    std::cout << "f is " << f << std::endl; //20

    auto &g = ci; // g is reference to const int ci, const is not top-level when bind reference to an initializer
    std::cout << "g is " << g << std::endl; //20
    const int *pi = &g;
    std::cout << "reference g has address? " << pi << std::endl;

    // auto &h = 42; error, cannot initializer a literal to plain reference
    const auto &j = 42; // j reference to a const int temperary
    std::cout << "j address is and j is " << &j << " " << j << std::endl;

    auto k = ci, &l = i; // k is int, l is a reference to int
    auto &m = ci, *p = &ci; //m is const int reference, p is pointer to const int, const int*

    // auto &n = i, *p2 = &ci; // error, n is int reference, p2 is pointer to const int

    a = 42;
    std::cout << "new a is " << a << std::endl; //42

    b = 42;
    std::cout << "new b is " << b << std::endl; //42

    c = 42;
    std::cout << "new c is " << c << std::endl; //42

    // d = 42; //error, 
    // e = 42; //error,

    // g = 42; //error, g is read only const int reference

    return 0;
}
