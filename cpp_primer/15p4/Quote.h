#ifndef QUOTE
#define QUOTE

#include <string>
#include <iostream>

class Quote{
public:
    Quote(){
        bookNo = ""; price = 0;
        std::cout << "Quote() called." << std::endl;
    };
    //virtual ~Quote() = default; //base class always has virtual destructor, even they do nothing
    virtual ~Quote(){
        std::cout << "~Quote() called." << std::endl;
    }
    Quote(const std::string& book, double sales_price):bookNo(book), price(sales_price){}

    std::string isbn() const {return bookNo;} //not virtual , resolved at compile time, not run-time

    //virtual keyword only in declaration, cannot in defination outside of class body
    //declared as virtual in base class also implicity declare as virtual in derived classs
    //dynamic binding, which version net_price() to call depend on object type, that can be made until run time
    virtual double net_price(std::size_t n) const {return n * price;}
    virtual void debug(std::ostream& os) const;

    //copy constructor
    Quote(const Quote& orig){
        bookNo = orig.bookNo;
        price =  orig.price;
        std::cout << "Quote copy construct." << std::endl;
    }

    //copy assignment
    Quote& operator=(const Quote& rhs){
        bookNo = rhs.bookNo;
        price = rhs.price;
        std::cout << "Quote copy assignment." << std::endl;
        return *this;
    }

    //move construct, do not use orig anymore
    Quote(Quote&& orig){
        bookNo = std::move(orig.bookNo);
        price = std::move(orig.price);
        //make orig safe to destruct
        //orig.bookNo = "";
        //orig.price = 0;
        std::cout << "Quote move construct." << std::endl;
    }

    //move assignment
    Quote& operator=(Quote&& rhs){
        if(this != &rhs){
            bookNo = std::move(rhs.bookNo);
            price = std::move(rhs.price);
            //make rhs safe to destruct
            //rhs.bookNo = "";
            //rhs.price = 0;
        }
        std::cout << "Quote move assignment." << std::endl;
        return *this;
    }

    //virtual clone() function return pointer to new allowcated memory
    virtual Quote* clone() const & { return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
    
private:
    std::string bookNo; //derived class member func cannot access, class user cannot
protected:
    double price = 0.0; //derived class member func can access, class user cannot
};

double print_total(std::ostream& os, const Quote& item, size_t n);


#endif