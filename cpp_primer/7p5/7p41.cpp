#include <iostream>
#include <string>
#include <vector>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

int main()
{

    // use non-delegating construtor
    Sales_data obj_d("aaa", 2, 11);
    std::cout << obj_d.bookNo << std::endl; // aaa
    std::cout << obj_d.units_sold << std::endl; // 2
    std::cout << obj_d.revenue << std::endl; // 22

    // use delegating default constructor 1
    Sales_data obj1;
    std::cout << obj1.bookNo << std::endl; // empty string
    std::cout << obj1.units_sold << std::endl; // 0
    std::cout << obj1.revenue << std::endl; // 0

    // use delegating constructor 2,
    Sales_data obj2("bbb");
    std::cout << obj2.bookNo << std::endl; // bbb
    std::cout << obj2.units_sold << std::endl; // 0
    std::cout << obj2.revenue << std::endl; // 0

    // use delegating constructor 3
    Sales_data obj3(std::cin); // input xyz 3 22
    std::cout << obj3.bookNo << std::endl; // xyz
    std::cout << obj3.units_sold << std::endl; // 3
    std::cout << obj3.revenue << std::endl; // 66

    return 0;
}