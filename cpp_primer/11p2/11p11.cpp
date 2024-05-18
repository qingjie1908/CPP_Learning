#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
        return lhs.isbn() < rhs.isbn();
}

int main()
{
    std::multiset<Sales_data, decltype(compareIsbn)*> bookstore1(compareIsbn);
    Sales_data obj1;
    Sales_data obj2("abc");
    Sales_data obj3("abc");
    Sales_data obj4("bc");

    std::vector<Sales_data> vec1 = {obj1, obj2, obj3, obj4};

    for (auto item : vec1){
        bookstore1.insert(item);
    }

    for(auto item : bookstore1){
        print(std::cout, item) << std::endl;
    }
    //output
    /*
     0 0 0
    abc 0 0 0
    abc 0 0 0
    bc 0 0 0
    */

    std::multiset<Sales_data, bool (*)(const Sales_data &lhs, const Sales_data &rhs)> bookstore2(&compareIsbn);
    for (auto item : vec1){
        bookstore2.insert(item);
    }

    for(auto item : bookstore2){
        print(std::cout, item) << std::endl;
    }
    //output
    /*
     0 0 0
    abc 0 0 0
    abc 0 0 0
    bc 0 0 0
    */
}