#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Disc_quote.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.h"

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.cpp"

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.cpp"
#include <vector>
#include <iostream>
#include <string>
#include <memory>

int main()
{
    std::vector<Quote> vec1;
    vec1.push_back(Quote("aaa", 10));
    vec1.push_back(Bulk_quote("bbb", 10, 10, 0.5, 100));

    std::cout << vec1.back().net_price(10) << std::endl;
    //intend to get 10*10*0.5 = 50,
    //but Bulk_quote obj will be sliced down, only get Quote part obj into vec1
    //so actually just get 10*10 = 100

    //When we need a container that holds objects related by inheritance, we typically define the container to hold pointers (preferably smart pointers) to the base class
    //can convert a smart pointer to a derived type to a smart pointer to an base-class type
    std::vector<std::shared_ptr<Quote>> vec2;
    vec2.push_back(std::make_shared<Quote>(Quote("aaa", 10)));
    vec2.push_back(std::make_shared<Bulk_quote>(Bulk_quote("bbb", 10, 10, 0.5, 100)));

    //it's like following:
    /*
    std::shared_ptr<Bulk_quote> sp_bulk_qupte = std::make_shared<Bulk_quote>(Bulk_quote("bbb", 10, 10, 0.5, 100));
    std::shared_ptr<Quote> sp_Quote;
    sp_Quote = sp_bulk_qupte; //coverted to base pointer
    */
    //then vec hold sp_Quote, all elements are std::shared_ptr<Quote> type

    std::cout << vec2.back()->net_price(10) << std::endl; //call func bind at run-time since this is virtual function
    //get 10*10*0.5 = 50;

    return 0;

}