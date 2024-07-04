#include <iostream>

template<typename F, typename T1, typename T2>
void flip(F f, T1&& t1, T2&& t2){ //T&& can bind any kind of argument
    //f(t2, t1); // here f is a callable object, without forward

    f(std::forward<T2>(t2), std::forward<T1>(t1)); //with forward
    //forward return a rvalue reference to that explicit argument type, that is forward<T2> is T2&&
}

void func(int& i, int&& j){
    std::cout << i << " " << j << std::endl;
}

int main(){

    int a1 = 3;
    int a2 = 5;
    flip(func, 5, a1); //3 5
    //F is void (*)(int&, int&&)
    //T1 is int, cause 5 is rvaue, T1&& is int&&, 
    //T2 is int&, cause a1 is lvalue, T2&& is int& &&, collapse to int&
    //instantiate void flip(int (*f)(int&, int&&), int&& t1, int& t2)
    //call flip(func, 5, a1); then int&& t1 = 5, int& t2 = a1; ok
    //now when call f(t2, t1), which is func(t2, t1)
    //int& i = t2; int&& j = t1
    //int& i = t2, t2 bind to a1, so i bind to a1, ok
    //int&& j = t1, t1 itself is lvalue, cannot bind rvalue reference to lvalue

    //if call forward version f
    //T1 is int, the forward<T1> become to int&&
    //T2 is int&, forward<T2> become to int& &&, collapse to int&
    //now when call f(t2, t1), it will not call f(t2, t1)
    //but call f(a1, 5);???

}