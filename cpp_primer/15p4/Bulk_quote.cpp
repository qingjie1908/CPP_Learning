#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.h"

//A derived class may access the public and protected members of its base class
double Bulk_quote::net_price(std::size_t cnt) const{
    if(cnt >= quantity && cnt <= max_qty){
        return cnt * (1 - discount) * price; //price is protected member from base class, can access
    } else if (cnt > max_qty){
        return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
    } else
        return cnt * price;

}