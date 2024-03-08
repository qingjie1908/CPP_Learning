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
};
// nonmember Sales_data interface functions
Sales_data add(const Sales_data&, const Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
#endif