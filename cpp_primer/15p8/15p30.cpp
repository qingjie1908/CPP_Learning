#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Disc_quote.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.h"

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Quote.cpp"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Bulk_quote.cpp"

#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <set>


class Basket{
public:
    //Basket use sythesized default constructor and copy-control members
    void add_item(const std::shared_ptr<Quote> &sale){
        item.insert(sale);
    }

    //when Basket obj, we need to call obj.add_item(make_shared<Quote>("123", 45))
    //or call obj.add_item(make_shared<Bulk_quote>("345", 45, 3, .15));
    //which is inconvenient, define another func to hide pointers
    //so user can call add_item more easily
    void add_item(const Quote&); //copy
    void add_item(Quote&&); //move

    //print total price for all the books
    //inside total_receipt, it will print price for books with same isbn
    double total_receipt(std::ostream& os) const;


private:

    //So a function should be static if its operation do not depend on instance (Basket obj) and if you require an action in your function that require this
    //static func does not have this pointer, so inside it, it access static class member or variable not belong to this
    static bool compare_bookNo(const std::shared_ptr<Quote>& sp_lhs, const std::shared_ptr<Quote>& sp_rhs){
        //const here, should not change sp_rhs pointed to contents, and pass by reference, not create a local shared_ptr to copy ptr value
        return sp_lhs->isbn() < sp_rhs->isbn();
    }

    //multiset use < operator to order same elements, and compare share_ptr itself is no use
    //so need to provide a function type pointer
    //note in-class intializer can only use "=" or {} form
    //so item(compare_bookNo) us wrong, use item{compare_bookNo}
    std::multiset<std::shared_ptr<Quote>, decltype(compare_bookNo)*> item{compare_bookNo};

};

double Basket::total_receipt(std::ostream& os) const{
    auto iter = item.cbegin(); //iter refer to element which point to shared_ptr<Quote>, dereference iter is a shared_ptr<Quote>
    double ret = 0; //prices for all books
    while(iter != item.cend()){
        //current_bookNo no use here, just for illustration
        std::string current_bookNo = (**iter).isbn(); //**iter, static type is Quote, look up name isbn() from Quote::, non-virtual func, no dynamic binding
        ret += print_total(os, **iter, item.count(*iter)); //print price for the same bookNo objects, and update total price, dynamic binding

        iter = item.upper_bound(*iter); //iter refer to element (shared_ptr), which bookNo is different
    }
    os << "Total prices for all books: " << ret << std::endl;
    return ret;
}

void Basket::add_item(const Quote& sale){
    //item.insert(std::shared_ptr<Quote>(new Quote(sale)));
    //shared_ptr<Quote> sp(p); use Quote* or BulkQuote* plain pointer p to initialize sp is ok, if derive to base conversion ok
    //shared_ptr<Quote> sp = new Quote(sale) is wrong, shared pointer and plain pointer are different type, cannot assign

    //problem is : new Quote(sale)), if sale is a BulkQuote type object, new Quote(sale) will only generator the Quote(obj), slice down the derived part
    //now what we wanted
    //that's why we do not use new Quote(sale)), but call the clone function
    //since clone func is virtual, it will generate obj based on sale obj dynamic type

    item.insert(std::shared_ptr<Quote>(sale.clone()));
}

void Basket::add_item(Quote&& sale){
    //note here sale is ravlue reference, is a variable, sale itself is still lvalue
    //so if we want to call the rvalue version clone(), we call it on std::move(sale)
    item.insert(std::shared_ptr<Quote>((std::move(sale)).clone()));
}

int main()
{
    Quote obj1("aaa", 10);
    Bulk_quote obj2("bbb", 10, 10, 0.5, 100);

    Basket my_basket;

    my_basket.add_item(obj1);
    my_basket.add_item(obj2);
    //use add item lvalue version, then call clone() const & lvalue version
    //so obj1 and obj2 still in stack memory
    //create new_obj1, new_obj2 in heap memory

    my_basket.add_item(std::move(obj1));
    my_basket.add_item(std::move(obj2));
    //use add item rvalue version, then call clone() && rvalue version
    //now obj1, obj2 contained contents moved to heap memory
    //now obj1, obj2.bookNo will be empty string
}








