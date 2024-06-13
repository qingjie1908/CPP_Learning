#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

int main()
{
    Sales_data obj1("AAA", 2, 10.0), obj2("BBB", 3, 9.1), obj3("CCC", 5, 5.5);

    std::string s1 = obj1; // "AAA"

    double d2 = obj2; //27.299999

    obj3 = "CCCC"; //call assginment operator=; obj3.bookNo = "CCCC now
    
    //if covnersion opearator is explicit, we need to use static_cast, implicit d2 = obj2 is error;
    d2 = static_cast<double>(obj2) + 1; //28.299999

    //if Sales_data has operator+(const Sales_data& obj, double d)
    
    //double dd = obj1 + 4.4;
    //ambiguous:
    //it can call Sales_data::oeprator+
    //or it can first convert obj1 to double, then use std::double + operator
}