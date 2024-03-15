#include <iostream>
#include <string>
#include <vector>

class Sales_data{
// aggregate clase if
// 1. all data member are public
// 2. not define any constructors
// 3. has no in-class initializer, here units_sold and revenue has in-class initializer 0, 0.0
// 4. has no base classeds or virtual function
public:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

class Debug{
// litreal class:
// 1. data member all have leteral tyoe
// 2. class must have at least one constexpr construtor
// 3. in-class initializer must be constant expression, if member has class type, intializer must use the member's own constexpr constructor

// constexpr Constructors:
// constructor body is empty
// must initialize every data member, the intializers must either use constexpr constructor or be a constant expression
public:
    constexpr Debug(bool b = true):hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i, bool o):hw(h), io(i), other(o){}
    constexpr bool any() const {return hw || io || other;}
    constexpr void set_io(bool b) {io = b;}
    void set_hw(bool b) {hw = b;}
    void set_other(bool b) {hw = b;}
private:
    bool hw; // hardware errors other than IO errors
    bool io; // IO errors
    bool other; // other errors
};

int main()
{
    Sales_data item = {"978-07679"};
    std::cout << item.bookNo << std::endl; //978-07679
    std::cout << item.units_sold << std::endl; //0
    std::cout << item.revenue << std::endl; //0

    // constexpr constructor is used to generate objects that are constexpr and for parameters or return types in constexpr functions:
    Debug io_sub(false, true, false); // debugging IO
    if(io_sub.any()) // equivalent to if(true)
    {
        std::cerr << "print appropriate error messages" << std::endl;
    }
    // if constexpr Debug prod(false)
    // then prod has type 'const Debug'
    // so member function 'any' should be const member function
    // const object can only call const member functions
    // non-const object can call both const and non-const member functions
    constexpr Debug prod(false); //no debugging during production
    if(prod.any()) // equivalent to if(false)
    {
        std::cerr << "print an error message" << std::endl;
    }

    return 0;
}

