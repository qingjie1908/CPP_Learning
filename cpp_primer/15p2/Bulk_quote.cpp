#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p2/Bulk_quote.h"
#include <iostream>

//a derived class must use a base-class constructor to initialize its base-class part
//The constructor body of a derived constructor can assign values to its public or protected base-class members, but should not do so
Bulk_quote::Bulk_quote(const std::string& book, double p, std::size_t qty_min, std::size_t qty_max, double disc):
                        Quote(book, p), min_qty(qty_min), max_qty(qty_max) ,discount(disc) {
                            //price = 3; legal but should not assign values to its public or protected base-class members
                            if(max_qty < min_qty){
                                std::cout << "invalid setting for number limit of discounted books, set max_qty = min_qty" << std::endl;
                                max_qty = min_qty;
                            }

                            if(discount > 1 || discount < 0){
                                std::cout << "invalid discount setting, set discount to 0." << std::endl;
                                discount = 0;
                            }
                        }


//A derived class may access the public and protected members of its base class
double Bulk_quote::net_price(std::size_t cnt) const{
    if(cnt >= min_qty && cnt <= max_qty){
        return cnt * (1 - discount) * price; //price is protected member from base class, can access
    } else if (cnt > max_qty){
        return max_qty * (1 - discount) * price + (cnt - max_qty) * price;
    } else
        return cnt * price;

}
