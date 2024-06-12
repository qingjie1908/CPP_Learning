#include <functional> //use library function Objects, bind
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

void func1(const int& i_p, int divider_p, std::modulus<int> obj_p){
    if(obj_p(i_p, divider_p) == 0){
        std::cout << i_p << " in this vec can be divisible by " << divider_p << std::endl;
    }
}

void func2(const int& i_p){
    std::cout << i_p << " ";
}


int main()
{
    std::vector<int> vec1 = {3, 231, 5, 754, 8576, 34, 768};

    int divider = 3;

    std::modulus<int> obj;

    decltype(func2)* fp = func2;

    std::for_each(vec1.begin(), vec1.end(), std::bind(func1, std::placeholders::_1, divider, obj));
    std::for_each(vec1.begin(), vec1.end(), fp);
    return 0;
}