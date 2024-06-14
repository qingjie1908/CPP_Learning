#ifndef QUOTE
#define QUOTE

#include <string>
#include <iostream>

class Quote{
public:
    Quote() = default;
    virtual ~Quote() = default; //base class always has virtual destructor, even they do nothing
    Quote(const std::string& book, double sales_price):bookNo(book), price(sales_price){}

    std::string isbn() const {return bookNo;} //not virtual , resolved at compile time, not run-time

    //virtual keyword only in declaration, cannot in defination outside of class body
    //declared as virtual in base class also implicity declare as virtual in derived classs
    //dynamic binding, which version net_price() to call depend on object type, that can be made until run time
    virtual double net_price(std::size_t n) const {return n * price;}
    virtual void debug(std::ostream& os) const;
    
private:
    std::string bookNo; //derived class member func cannot access, class user cannot
protected:
    double price = 0.0; //derived class member func can access, class user cannot
};

double print_total(std::ostream& os, const Quote& item, size_t n);


#endif