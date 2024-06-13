#include <iostream>

struct LongDouble{
    LongDouble(double p = 0.0){}
    operator double() {return 1.1;}
    operator int() {return 2;}
};

void calc(int) {std::cout << "call calc(int)" << std::endl; }
void calc(LongDouble) {std::cout << "call calc(LongDouble)" << std::endl;}

int main(){
    LongDouble ldObj; //ok, use default argument 0.0 for double parameter in constructor
    int ex1 = ldObj; //ok , conversion operator int() is a exact match
    //float ex2 = ldObj; //error, both conversion operator not exact match, can call either of them, then convert that result to float

    double dval = 3.3;
    calc(dval);
    //ambiguous, 
    //although for calc(int), it need convert dval to int 3 first
    //for calc(LongDouble), it use the default constructor
    //seems the calc(LongDouble) is exact mathc, but
    //they are different user-defined conversions from one another
    //so the rank does not have effect, ambiguous 
    //use g++ compile, this calls the calc(int) version

    //unlike int ex1 = ldObj; operator double() and operator int() are both user defined, so exact match matter

    //in calc, one is useing LongDouble-Defined, one is using built_in-defined conversion, LongDouble and built_in are two different user
    //so for two different user-difined, the convert rank does not have effect, still ambiguous
    //but since one user is built-in, standard conversion, so choose calc(int)
    //if both user are class type, then ambiguous

    return 0;
}