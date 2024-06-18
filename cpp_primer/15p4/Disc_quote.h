#ifndef DISCQUOTE
#define DISCQUOTE

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.h"
#include <string>
//A class containing (or inheriting without overridding) a pure virtual function is an abstract base class
//cannot (directly) create objects of a type that is an abstract base class
class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, std::size_t qty = 0, double disc = 0):
        Quote(book, price), quantity(qty), discount(disc){
            if(discount > 1 || discount < 0){
                                std::cout << "invalid discount setting, set discount to 0." << std::endl;
                                discount = 0;
            }
        }
    //Although we cannot define objects of this type directly, 
    //constructors in classes derived from Disc_quote will use the Disc_quote constructors to construct the Disc_quote part of their objects.

    double net_price(std::size_t) const = 0;

    std::pair<std::size_t, double> discount_pilicy() const
        { return {quantity,  discount};}

    Disc_quote(const Disc_quote& orig):Quote(orig){
        //important !!!
        //Quote(orig) in constructor initializer list is construct the Quote part of Disc_quote object;

        //Quote(orig) inside constructor function body
        //it's just creating a temporary, unnamed and new object of type Quote.
        //It will be destroyed as the constructor exits!!!!
        //Quote(orig); //creating a temporary, unnamed and new object of type Person., will be destroyed outside of class
        quantity = orig.quantity;
        discount = orig.discount;
        std::cout << "Disc_quote copy constrcut." << std::endl;
    }

    Disc_quote& operator=(const Disc_quote& rhs){
        Quote::operator=(rhs);
        quantity = rhs.quantity;
        discount = rhs.discount;
        std::cout << "Disc_quote copy assignment." << std::endl;
        return *this;
    }

    Disc_quote(Disc_quote&& orig):Quote(std::move(orig)){ 
        //Quote(orig) in member initialize list will call Quote copy constrcut, not move construct
        //Disc_quote&& orig = std::move(arguments), now orig itself is variable, a lvalue!!!
        //Quote(std::move(orig)) will move the Base Quote part, remainig part leave to Disc_quote move constructor
        quantity = std::move(orig.quantity);
        discount = std::move(orig.discount);
        //make orig safe to destruct
        //orig.quantity = 0;
        //orig.discount = 0;
        std::cout << "Disc_quote move constrcut." << std::endl;
    }

    Disc_quote& operator=(Disc_quote&& rhs){
        if(this != &rhs){
            Quote::operator=(std::move(rhs)); //rhs itself is variable, lvalue
            quantity = std::move(rhs.quantity);
            discount = std::move(rhs.discount);
            //make rhs safe to destruct
            //rhs.quantity = 0;
            //rhs.discount = 0;
        }
        std::cout << "Disc_quote move assignment." << std::endl;
        return *this;
    }

    ~Disc_quote(){
        std::cout << "Disc_quote destructor called." << std::endl;
    }

protected:
    std::size_t quantity = 0;
    double discount = 0;
};

#endif