#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
struct Sales_data {
    // new members: operations on Sales_data objects
    // A "const function", denoted with the keyword const after a function declaration, 
    // makes it a compiler error for this class function to change a data member of the class. 
    // However, reading of a class variables is okay inside of the function, 
    // but writing inside of this function will generate a compiler error.
    // see https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    // data members are unchanged as follows
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
    // add constructors
    // first only initialize bookNo
    Sales_data(const std::string &s):bookNo(s){}
    // second only initialize units_sold and revenue y
    Sales_data(unsigned int x, double y): units_sold(x), revenue(y) {}
    //thrid use default initializer
    Sales_data() = default;
};
// nonmember Sales_data interface functions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
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