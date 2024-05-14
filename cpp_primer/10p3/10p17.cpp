
#include <iostream>
#include <vector>
#include <string>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

/*
bool compareIsbn(Sales_data& obj1, Sales_data&obj2)
{
    return obj1.isbn() > obj2.isbn();
}
*/

int main()
{
    Sales_data obj1("abc");
    Sales_data obj2("bcd");
    Sales_data obj3("cde");
    Sales_data obj4("abcd");
    Sales_data obj5("a");

    std::vector<Sales_data> vec_sd = {obj1, obj2, obj3, obj4, obj5};

    
    //print original object in vec_sd
    for(auto item : vec_sd){
        print(std::cout, item); //print func is defined in header file
        std::cout << std::endl;
    }
    /*
    abc 0 0 0
    bcd 0 0 0
    cde 0 0 0
    abcd 0 0 0
    a 0 0 0
    */


    //std::sort(vec_sd.begin(), vec_sd.end(), compareIsbn); //predicate compareIsbn put large isbn string object at first
    // rewrite predicate using lambda expression

    std::sort(vec_sd.begin(), vec_sd.end(), [](Sales_data obj1, Sales_data obj2){return obj1.isbn() > obj2.isbn();});
    
    for(auto item : vec_sd){
        print(std::cout, item);
        std::cout << std::endl;
    }
    /*
    cde 0 0 0
    bcd 0 0 0
    abcd 0 0 0
    abc 0 0 0
    a 0 0 0
    */

    return 0;
}