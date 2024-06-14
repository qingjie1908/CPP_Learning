#ifndef BULKQUOTE
#define BULKQUOTE

#include <string>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p2/Quote.h"

//access specifier used in a derivation list
//determines whether users of a derived class are allowed to know that the derived class inherits from its base class.
// derivation is public, the public members of the base class become part of the interface of the derived class as well
//so for class Bulk_quote : public Quote, Bulk_quote obj_derived, obj_derived.isbn() and print_total(std::cout, obj_derived, 10) is ok
//if class Bulk_quote : public Quote,  Bulk_quote obj_derived, obj_derived.isbn() and print_total(std::cout, obj_derived, 10) is illegal, only obj_derived.net_price() is ok

//but note, even class Bulk_quote : private Quote
//inside Quote class, we can still call like std::stirng ss = isbn();
//its like, when we defind class Bulk_Quote, the class Bulk_Quote itself is the user of Quote
//so in Bulk_Quote class defination, whether it can use isbn() or price or bookNo depends on whether these member/func are public/protected in class Quote or private in class Quote
//so in class Bulk_quote : private Quote{}, std::string ss = this->isbn(); double dd = price; is ok, since they are public in class Quote, ss = bookNo; is illegal, since it's private in class Quote

//when we define Bulk_Quote obj_derived; obj_derived is the user of derived Bulk_quote, not Quote
//so obj_derived.net_price() is ok,
//printe_total(obj_derived) and obj_derived.isbn() is ok or not depend on the access specifier in derivation list

//so user "class Bulk_quote" of "class Quote" can access which depend on the access specifier inside base class "Quote"
//user obj_derived of "class Bulk_quote" can access which depend on the access specifier inside "class Bulk_Quote",
//obj_derived whether can access base class public member and be treated as base class object, depends on the access specifier in the derivation list

//When the derivation is public, the public members of the base class become part of the interface of the derived class as well. 
//In addition, we can bind an object of a publicly derived type to a pointer or reference to the base type.

class Bulk_quote : public Quote{
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string&, double, std::size_t, std::size_t, double);

    double net_price(std::size_t) const override;

    void debug(std::ostream& os) const override;
    
private:
    std::size_t min_qty = 0;
    std::size_t max_qty = 50; //like purchase 51 books, then 50 book has discount, 1 book remaning use original price
    double discount = 0.0;
};

#endif
