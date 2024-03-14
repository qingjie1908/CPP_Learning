#include <iostream>
#include <string>
#include <vector>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

Sales_data first_item(std::cin); // example input abcd 10 33

int main()
{
    Sales_data next;
    Sales_data last("9-999-99999-9");
    std::cout << "next.bookNo is: " << next.bookNo << std::endl; // acy
    std::cout << "next.units_sold is: " << next.units_sold << std::endl; //0
    std::cout << "next.revenue is: " << next.revenue << std::endl;//0
    std::cout << "last.bookNo is: " << last.bookNo << std::endl; // 9-999-99999-9
    std::cout << "last.units_sold is: " << last.units_sold << std::endl; //0
    std::cout << "last.revenue is: " << last.revenue << std::endl;//0
    std::cout << "first_item.bookNo is: " << first_item.bookNo << std::endl; //abcd
    std::cout << "first_item.units_sold is: " << first_item.units_sold << std::endl; //10
    std::cout << "first_item.revenue is: " << first_item.revenue << std::endl; //330
    return 0;
}