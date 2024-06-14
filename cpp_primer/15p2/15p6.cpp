#include <iostream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p2/Bulk_quote.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p2/Quote.h"

int main()
{
    Quote obj_base("aaa", 10);
    Bulk_quote obj_derived("bbb", 20, 10, 100, 0.3); //when size > 10, discount 0.3, (1-0.3)

    std::cout << obj_base.isbn() << std::endl;
    double net_obj_base =  print_total(std::cout, obj_base, 20);

    //"derived class" can access base class public and protected member and member function
    //cause here "derived class" is the user of class base, can access base class public (interface), and protected member/member func

    //but object of derived class cannot access non-virtual func in base class if the access specifier is private in derivation list
    //cause object_derived is the user of class derived, so it can only call class derived public (interface)
    //if it want access base_class public member also, then access specifier need to be public in derivation list
    
    //std::cout << obj_derived.isbn() << std::endl; error, isbn() is not virtual in base, only avaible to base class users (which is a object of base class and derived class)
    double net_obj_derived = print_total(std::cout, obj_derived, 20);
    std::cout << obj_derived.isbn() << std::endl;

    //output
    /*
    aaa
    ISBN: aaa # sold: 20 total due: 200
    ISBN: bbb # sold: 20 total due: 280
    bbb
    */

    Bulk_quote obj2("ccc", 10, 10, 9, 0.3);
    double net_obj2 = print_total(std::cout, obj2, 20);

    Bulk_quote obj3("ddd", 10, 10, 9, 1.1);
    double net_obj3 = print_total(std::cout, obj3, 20);

    Bulk_quote obj4("eee", 10, 10, 20, 0.5);
    double net_obj4 = print_total(std::cout, obj4, 30);

    //output
    /*
    invalid setting for number limit of discounted books, set max_qty = min_qty
    ISBN: ccc # sold: 20 total due: 170
    invalid setting for number limit of discounted books, set max_qty = min_qty
    invalid discount setting, set discount to 0.
    ISBN: ddd # sold: 20 total due: 200
    ISBN: eee # sold: 30 total due: 200
    */
    return 0;
}