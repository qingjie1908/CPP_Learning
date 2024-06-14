#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p2/Quote.h"
#include <iostream>
double print_total(std::ostream& os, const Quote& item, size_t n){
    double ret = item.net_price(n);
    os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
    return ret;
}