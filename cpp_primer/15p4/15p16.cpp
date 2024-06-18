#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.h"
#include <string>
#include <iostream>

int main()
{
    Quote obj("aaa", 10);
    print_total(std::cout, obj, 10);
    //ISBN: aaa # sold: 10 total due: 100

    //Disc_quote obj_abstract_class; //object of abstract class type "Disc_quote" is not allowed:

    Bulk_quote obj_bulk1("bbb", 10, 10, 0.3, 20);
    print_total(std::cout, obj_bulk1, 25);
    //ISBN: bbb # sold: 25 total due: 190

    Bulk_quote obj_bulk2("ccc", 10, 10, 20, 20); //discount set to 20, not in [0,1]
    print_total(std::cout, obj_bulk2, 15);
    //invalid discount setting, set discount to 0.
    //ISBN: ccc # sold: 15 total due: 150

    Bulk_quote obj_bulk3("ccc", 10, 10, 0.5, 5); //max_limit set to 5, <10
    print_total(std::cout, obj_bulk3, 5);
    //invalid setting for number limit of discounted books, set max_qty = quantity
    //ISBN: ccc # sold: 5 total due: 50

    {
        Quote obj1(obj); //Quote copy construct.
        Quote obj2(std::move(obj)); //Quote move construct.
        obj2 = obj1; //Quote copy assignment.
        obj2 = std::move(obj1); //Quote move assignment.

        Bulk_quote objj1(obj_bulk1); //Quote copy construct. Disc_quote copy constrcut. Bulk_quote copy construct.
        Bulk_quote objj2(std::move(obj_bulk1)); //Quote move construct. Disc_quote move constrcut. Bulk_quote move construct.
        objj2 = objj1; //Quote copy assignment. Disc_quote copy assignment. Bulk_quote copy assignment.
        objj2 = std::move(objj1); //Quote move assignment. Disc_quote move assignment. Bulk_quote move assignment.
    }
    //objj2:
    //Bulk_quote destructor called.
    //Disc_quote destructor called.
    //~Quote() called.

    //objj1:
    //Bulk_quote destructor called.
    //Disc_quote destructor called.
    //~Quote() called.

    //obj2:
    //~Quote() called.

    //obj1
    //~Quote() called.

    return 0;
    //destructor for obj_bulk3, obj_bulk2, obj_bulk1, obj
    //Bulk_quote destructor called.
    //Disc_quote destructor called.
    //~Quote() called.
    //Bulk_quote destructor called.
    //Disc_quote destructor called.
    //~Quote() called.
    //Bulk_quote destructor called.
    //Disc_quote destructor called.
    //~Quote() called.
    //~Quote() called.

}