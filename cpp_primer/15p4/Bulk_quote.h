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

private:
    //since we only decide max_qty strategy for Bulk_quote class, so max_qty be a member of B ulk_quote, not Disc_quote
    //cause there may be other strage inherit from Disc_quote that does not set limit on max_qty
    //basically, all strategy class at least have one qty setting, so that setting in abstract base class Disc_quote
    std::size_t max_qty = 0; //max quantity that can have discount 
};

#endif