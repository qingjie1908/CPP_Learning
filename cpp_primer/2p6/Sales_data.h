#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
// pwd, /Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h
class Sales_data {
// add friend declaration of nonmember function add() print() read(), otherwise these non-member func cannot use Sales_data private members
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
public: // usually constructors and some member functions are public
    // add constructors
    // first only initialize bookNo
    Sales_data(const std::string &s):bookNo(s){}
    // second only initialize units_sold and revenue y
    Sales_data(unsigned int x, double y): units_sold(x), revenue(y) {}
    //thrid use default initializer
    // Sales_data() = default; // only if the compiler support in-class initilizers for this class data members
    // add declaration only, no defination of another constructor
    Sales_data(std::istream &is);
    //fifth, another default constructor when conpliler does not supprot in-class initializers, we should use the constructor initializer list to initialize every member of the class
    // since this constructor take no arguments, it is a default constructor, then we should not keep Sale_data() = default, otherwise it is re-declaration default constructor
    Sales_data():bookNo("abc"), units_sold(11),revenue(100){}
    // new members: operations on Sales_data objects
    // A "const function", denoted with the keyword const after a function declaration, 
    // makes it a compiler error for this class function to change a data member of the class. 
    // However, reading of a class variables is okay inside of the function, 
    // but writing inside of this function will generate a compiler error.
    // see https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
private:
    double avg_price() const;
    // data members are unchanged as follows
    std::string bookNo;
    unsigned units_sold = 0; // this 0 only effect when use Sales_data() = default;
    double revenue = 0.0; // this 0.0 only effect when use Sales_data() = default;

};
// nonmember Sales_data interface functions, outside class ordinary declaration needed even we have friend declaration inside class
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
// defining a constructor outside the class body, must be declared inside class first
// this constructor define must be put after function declaration read(), other wise it will not find read
Sales_data::Sales_data(std::istream &is)
{
    read(is, *this); // when detect 3 inputs, it will match to *this bookNo, units_sold and price, then jump to next expression if cin is not in while loop
}
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this; // if we declare object Sales_data total; then call total.combine(trans), then *this return 'total' object
}
double Sales_data::avg_price() const
{
    if (units_sold)
        return revenue/units_sold;
    else
        return 0;
}
std::istream &read(std::istream &is, Sales_data &item)
{
    double price = 0;
    is >> item.bookNo >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}
std::ostream &print(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
    << item.revenue << " " << item.avg_price();
    return os;
}
Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
#endif