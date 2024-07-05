#include <iostream>

template<typename T> void f(T){std::cout << "call 1" << std::endl;}
template<typename T> void f(const T*){std::cout << "call 2" << std::endl;}
template<typename T> void g(T){std::cout << "call 3" << std::endl;}
template<typename T> void g(T*){std::cout << "call 4" << std::endl;}

int main()
{
    int i = 42, * p = &i;
    const int ci = 0, * p2 = &ci;

    g(42); //void g<int>(int); call 3 only,
    g(p); //void g<int>(int*); 3 viable, call 4 exact match
    g(ci); //void g<int>(int); call 3 only,ci not reference, top level const ignored,
    g(p2); //void g<const int>(const int*); 3 viable, call 4, more specilization

    f(42); //void f<int>(int); call 1 only
    f(p); //void f<int*>(int*); call 1; 2 viable, but 1 best match, since 2 has conversion to const
    f(ci); //void<int>f(int); call 1 only, ci not reference, top level const ignored,
    f(p2); //void<int>f(const int*); 1 vibale, but call 2, best match

    /*
    call 3
    call 4
    call 3
    call 4
    3*call 1
    call 2
    */

}