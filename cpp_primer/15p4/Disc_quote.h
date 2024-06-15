#ifndef DISCQUOTE
#define DISCQUOTE

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.h"

//A class containing (or inheriting without overridding) a pure virtual function is an abstract base class
//cannot (directly) create objects of a type that is an abstract base class
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, std::size_t qty, double disc):
        Quote(book, price), quantity(qty), discount(disc){
            if(discount > 1 || discount < 0){
                                std::cout << "invalid discount setting, set discount to 0." << std::endl;
                                discount = 0;
            }
        }
    //Although we cannot define objects of this type directly, 
    //constructors in classes derived from Disc_quote will use the Disc_quote constructors to construct the Disc_quote part of their objects.

    double net_price(std::size_t) const = 0;

protected:
    std::size_t quantity = 0;
    double discount = 0;
};

#endif