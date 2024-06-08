#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>
#include <iostream>
// pwd, /Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h
class Sales_data {
// add friend declaration of nonmember function add() print() read(), otherwise these non-member func cannot use Sales_data private members
friend Sales_data add(const Sales_data&, const Sales_data&);
friend std::ostream &print(std::ostream&, const Sales_data&);
friend std::istream &read(std::istream&, Sales_data&);
friend std::ostream& operator<<(std::ostream& os, const Sales_data& obj);
friend std::istream& operator>>(std::istream& is, Sales_data& obj);
friend Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs);
public: // usually constructors and some member functions are public
    // add constructors

    // page 290: defines the default constructor as well as one that takes a string argument
    // this construtor severs as two constructors
    // first is default constructor, when Sales_data object; object.bookNo has default value acy
    // second as constructor takes argument, when Sale_data object("abcd"); object.bookNo has value abcd
    // although inside () is not empty, but it provide parameter s with default argument "acy", so it can be omitted when Sales_data object, using default construtor version of this
    // or it can Sales_data("sdfas"), using argument "sdfas" to replace default argument "acy", this time this constructor is not using its default cosntrutor version
    // if s has no default argument, then it cannot serve as default construtor
    // Sales_data(std::string s = "acy"):bookNo(s){}

    // if want to supply cin as default argument to the constructor that takes an istream&
    // it will server as two construtors
    // first default constructor, when provide no argment, Sales_data object, object will take default argument std::cin
    // second serve as user defined constructor, Sales_data object(std::cin) or Sales_data object(std::cout) ...
    // but remember each class only has one default constructor, there cannot be another construtor takes default argument as default constructor in this class
    // which means has Sales_data(std::string s = "acy"):bookNo(s){} at the same time is error
    // Sales_data(std::istream &is = std::cin);

    // nondelegating constructor
    Sales_data(std::string s, unsigned cnt, double price):bookNo(s), units_sold(cnt), revenue(cnt * price){
        std::cout << "This is non-delegationg constructor initialize members from corresponding arguments." << std::endl;
    }
    // delegating constructor 1: default construtor to delegate intilization to nondelegating constructor
    Sales_data():Sales_data("", 0, 0) {
        std::cout << "Default constructor delegate to nondelegating construtor with three parameters." << std::endl;
    }
    // delegating constructor 2: constructor takes a string delegates to three-argument version
    explicit Sales_data(std::string s): Sales_data(s, 0, 0) {
        std::cout << "Construtor takes only string s then delegate to nondelegating construtor with three parameters." << std::endl;
    }
    // delegating constructor 3: construtor takes istream then delegate to default constructor then execute this delegate function body
    Sales_data(std::istream &is):Sales_data(){
        std::cout << "Constructor takes istream delegate to default construtor" << std::endl
        << "After default construtor finish member initialization and its function body" << std::endl
        << "Back to this construtor and finish its own funtion body" << std::endl;
        read(is, *this); 
    }


    // first only initialize bookNo
    // Sales_data(const std::string &s):bookNo(s){}

    // second only initialize units_sold and revenue y
    Sales_data(unsigned int x, double y): units_sold(x), revenue(y) {}

    //thrid use default initializer
    // Sales_data() = default; // only if the compiler support in-class initilizers for this class data members

    // add declaration only, no defination of another constructor
    // Sales_data(std::istream &is);

    //fifth, another default constructor when conpliler does not supprot in-class initializers, we should use the constructor initializer list to initialize every member of the class
    // since this constructor take no arguments, it is a default constructor, then we should not keep Sale_data() = default, otherwise it is re-declaration default constructor
    // Sales_data():bookNo("abc"), units_sold(11),revenue(100){}

    // new members: operations on Sales_data objects
    // A "const function", denoted with the keyword const after a function declaration, 
    // makes it a compiler error for this class function to change a data member of the class. 
    // However, reading of a class variables is okay inside of the function, 
    // but writing inside of this function will generate a compiler error.
    // see https://stackoverflow.com/questions/3141087/what-is-meant-with-const-at-end-of-function-declaration
    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);

    //overloaded operator
    //compound-assignmnet
    Sales_data& operator+=(const Sales_data& rhs);

public:
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
/*
Sales_data::Sales_data(std::istream &is)
{
    read(is, *this); // when detect 3 inputs, it will match to *this bookNo, units_sold and price, then jump to next expression if cin is not in while loop
}
*/
Sales_data& Sales_data::combine(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this; // if we declare object Sales_data total; then call total.combine(trans), then *this return 'total' object
}
inline double Sales_data::avg_price() const
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

//overload operator
//input, non-member func, if member func, can only have 1 parameter
std::istream& operator>>(std::istream& is, Sales_data& obj){
    double price;
    is >> obj.bookNo >> obj.units_sold >> price;
    if(is){ //check if is is in valid state
        //successful,
        obj.revenue = obj.units_sold * price;
    } else{ //in vaild, for example an string is is give to obj.units_sold, type mismatch, exception occur
        obj = Sales_data(); //reset obj to default state, copy assignment
        is.setstate(std::ios_base::failbit);
        std::cout << "Input for Sales_data item failed. Reset Sales_data item to empty" << std::endl;
    }
    //if not check is, when is fail, for example input "aaa, 1, aa", obj.bookNo = aaa, units_sold = 1, but price will be set to 0
    //and is.rdstate() will change from 0 to 4 (cause is::failbit is 4), is.fail() is true, cannot use is again

    return is;
}

//output
std::ostream& operator<<(std::ostream& os, const Sales_data& obj){
    os << obj.isbn() << " " << obj.units_sold << " "
        << obj.revenue << " " << obj.avg_price();
    return os;
}

//addition
Sales_data operator+(Sales_data obj1, Sales_data obj2);

//+= operator
Sales_data& Sales_data::operator+=(const Sales_data& rhs){
    if(bookNo != rhs.bookNo){
        std::cout << "cannot process books with different bookNo." << std::endl;
        return *this; //did not change 'this'
    }
    units_sold += rhs.units_sold; //use std::+=
    revenue += rhs.revenue; //use std::+=
    return *this;
}

//ex 14.13 + operator, should return a new obj, non-member func
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs){
    Sales_data sum = lhs; //copy construct
    sum += rhs; //use Sales_data::operator+=
    return sum;
}


