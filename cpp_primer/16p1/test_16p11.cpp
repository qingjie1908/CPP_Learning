#include <iostream>
#include <vector>
// template<typename T>
// void func1(T obj);

template<typename T>
void func1(T obj){
    std::cout << obj.mem1 << std::endl;
}

template<typename U> class A{
friend void func1<>(A<U> obj);
public:
    A(U p):mem1(p){}
private:
    U mem1;
};

int main()
{
    A<int> a(22);
    func1(a);

    int bb = int();
    std::vector<int> aa = {2,3,54,6};
    
}

