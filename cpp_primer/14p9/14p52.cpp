#include <iostream>

class SmallInt {
    friend
    SmallInt operator+(const SmallInt&, const SmallInt&){std::cout << "SmallInt.operator+() call" << std::endl; return SmallInt(33);} 
public:
    explicit SmallInt(int p = 0){val = p;} // conversion from int
    operator int() const { std::cout << "call SmallInt::int()" << std::endl; return val; } // conversion to int 
private:
    std::size_t val;
};

struct LongDouble {
    // member operator+ for illustration purposes; + is usually a nonmember 
    LongDouble operator+(const SmallInt&){std::cout << "call LongDouble.oeprator+()" << std::endl; return LongDouble(10);}
    // other members as in § 14.9.2 (p. 587)
    LongDouble(double p = 0.0){}
    operator double() {return 1.1;}
    operator int() {return 2;}
};

LongDouble operator+(LongDouble&, double) { std::cout << "call nonmeber operator+" << std::endl; return LongDouble(20);}

int main()
{
    SmallInt si;
    LongDouble ld;
    //ld = si + ld; error
    //first call si.operator+()
    //so ld need to change to a SmallInt obj
    //so first it can call ld.int(), then use int to construct SmallInt obj
    //or it can call ld.double(), then double transter to int, then construct SmallInt
    //since the second conversion first involve user:LongDouble double conversion operator, then involve standard conversion double to int
    //the first invlov user::LongDouble conversion int operator, 
    //for same user LongDouble, it did not know which to call cause both are ok, so ambigous error
    //antoher user standart covnersion does not affect the user LongDouble choose, both double() int() are ok

    ld = ld + si;
    //if use ld.oeprator+() call, then call directly, compiler choose this one
    //if use nonmember + call, then call si.int() first to converst si to int, then standard conversion convert int to double, then use nonmember call

    SmallInt s1;
    double d = s1 + 3.14;
    //first it can call s1.int(), convert s1 to int 0 then standart conversion to double 0.0, then add 3.14 use built_in arithmetic operator +
    //or it can construct SmallInt from 3.14, first standart convert 3.14 to int 3, then to obj, then call s1.operator+(), then get SmallInt obj, then call int() to convert to int, then standart conversion convert int to double then give it to d
    //so two match, built_in arithmetic + and SmallInt::operator+, ambiguous

    //if we made SmallInt constructor explicit , then it will only match arithmetic +, call s1.int() conversion

}


