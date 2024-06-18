#ifndef BULKQUOTE
#define BULKQUOTE

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Disc_quote.h"

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price, std::size_t qty, double disc, std::size_t max_limit):
                Disc_quote(book, price, qty, disc), max_qty(max_limit){
                    if (max_limit < qty){
                        std::cout << "invalid setting for number limit of discounted books, set max_qty = quantity " << std::endl;
                        max_qty = quantity;
                    }
                }
    //Bulk_quote has a direct base class, Disc_quote, and an indirect base class, Quote.
    //A Derived Class Constructor Initializes Its Direct Base Class Only
    //Quote part initialization id done when calling dierect base constructor

    double net_price(std::size_t) const override;

    Bulk_quote(const Bulk_quote& orig):Disc_quote(orig){
        //Disc_quote(orig) in constructor initializer list is construct the Quote part of Disc_quote object;

        //inside constructor function body
        //Disc_quote(orig) is creating a temporary, unnamed and new object of type Disc_quote
        //after this scope, it will be destroyed
        //Since Disc_quote is abstract class, create an object of its type will be an error
        //Disc_quote(orig); //error
        max_qty = orig.max_qty;
        std::cout << "Bulk_quote copy construct." << std::endl;
    }

    Bulk_quote& operator=(const Bulk_quote& rhs){
        Disc_quote::operator=(rhs);
        max_qty = rhs.max_qty;
        std::cout << "Bulk_quote copy assignment." << std::endl;
        return *this;
    }

    Bulk_quote(Bulk_quote&& orig):Disc_quote(std::move(orig)){ //orig itself is a variable, it's lvalue
        max_qty = std::move(orig.max_qty);
        //make orig safe to destruct
        //orig.max_qty = 0;
        std::cout << "Bulk_quote move construct." << std::endl;
    }

    Bulk_quote& operator=(Bulk_quote&& rhs){
        if(this != &rhs){
            Disc_quote::operator=(std::move(rhs));//rhs itself is a variable, it's lvalue
            max_qty = std::move(rhs.max_qty);
            //make rhs safe to destruct
            //rhs.max_qty = 0;
        }
    
        std::cout << "Bulk_quote move assignment." << std::endl;
        return *this;
    }

    ~Bulk_quote(){
        std::cout << "Bulk_quote destructor called." << std::endl;
    }


private:
    //since we only decide max_qty strategy for Bulk_quote class, so max_qty be a member of B ulk_quote, not Disc_quote
    //cause there may be other strage inherit from Disc_quote that does not set limit on max_qty
    //basically, all strategy class at least have one qty setting, so that setting in abstract base class Disc_quote
    std::size_t max_qty = 0; //max quantity that can have discount 
};

#endif