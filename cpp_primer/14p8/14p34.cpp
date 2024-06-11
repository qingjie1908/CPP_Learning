#include <iostream>

class if_then_else{
public:
    if_then_else(int n):x(n){}
    int operator()(int x1, int x2, int x3){
        if (x1 > x){
            return x2;
        } else {
            return x3;
        }
    }

private:
    int x;
};

int main()
{
    if_then_else obj1(5);

    std::cout << obj1(6, 7, 8) << std::endl; //7
    std::cout << obj1(3, 7, 8) << std::endl; //8

    return 0;

}