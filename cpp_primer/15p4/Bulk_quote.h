#ifndef BULKQUOTE
#define BULKQUOTE

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p4/Disc_quote.h"

class Bulk_quote : public Disc_quote {
public:
    Bulk_quote() = default;
    Bulk_quote(const std::string& book, double price, std::size_t qty, double disc, std::size_t max_limit):
                Disc_quote(book, price, qty, disc), max_qty(max_limit){
                    if (max_limit < qty){
                        std::cout << "invalid setting for number limit of discounted books, set max_qty = quantity " << std::endl;
                        max_qty = quantity;
                    }
                }
    //Bulk_quote has a direct base class, Disc_quote, and an indirect base class, Quote.
    //A Derived Class Constructor Initializes Its Direct Base Class Only
    //Quote part initialization id done when calling dierect base constructor

    // ex 15.27:
    //a constructor using declaration does not change the access level of the inherited constructor(s)
    //When applied to a constructor, a using declaration causes the compiler to gen- erate code for the derived constructor
    //for each constructor in the base class, the compiler generates a constructor in the derived class that has the same parameter list, and empty function body
    //default arguments in direct base constructor are not inherited
    //using Disc_quote::Disc_quote;
    //then Disc_quote:: all constructor will be seen in this scope (access is also inherited) and comipler generate code for them
    //default, copy, and move constructors are not inherited
    //so below are inherited Disc_quote:: user defined contructors, default arguments are not inherited, only keep paramter
    //will generate three contructor, each omit one parameter that has default arguments in the direct Base constructor
    //so generate total 3 version constructor as follows:
    //Bulk_quote(const std::string& book, double price, std::size_t qty, double disc):Disc_quote(const std::string& book, double price, std::size_t qty, double disc){}  //the data member max_qty in derived class are default intialized
    //Bulk_quote(const std::string& book, double price, std::size_t qty):Disc_quote(const std::string& book, double price, std::size_t qty){}
    //Bulk_quote(const std::string& book, double price):Disc_quote(const std::string& book, double price){}

    //if we have own defined Bulk_quote constructor that has same paramter list as inherited direct Base constructor, then that direct Base constructor will not be inherited

    //so now if we do not define own Bulk_quote constructor, and using Disc_quote::Disc_quote;
    //then in main() we can create Bulk_quote obj as follows
    // Bulk_quote obj_0; use Bulk_quote default constructor
    // Bulk_quote obj_1("aa", 10); use inherited constructor 1
    // Bulk_quote obj_2("aa", 10, 10); use inherited constructor 2
    // Bulk_quote obj_3("aa", 10, 10, 10); use inherited constructor 3

    //if add own defined constructor with four paramter, then Bulk_quote obj_3("aa", 10, 10, 10) will use own-defined, it will not inherit the four parameter version from direct base

    //So in Bulk_quote(): member intializer list, we can call
    double net_price(std::size_t) const override;

    Bulk_quote(const Bulk_quote& orig):Disc_quote(orig){
        //Disc_quote(orig) in constructor initializer list is construct the Quote part of Disc_quote object;

        //inside constructor function body
        //Disc_quote(orig) is creating a temporary, unnamed and new object of type Disc_quote
        //after this scope, it will be destroyed
        //Since Disc_quote is abstract class, create an object of its type will be an error
        //Disc_quote(orig); //error
        max_qty = orig.max_qty;
        std::cout << "Bulk_quote copy construct." << std::endl;
    }

    Bulk_quote& operator=(const Bulk_quote& rhs){
        Disc_quote::operator=(rhs);
        max_qty = rhs.max_qty;
        std::cout << "Bulk_quote copy assignment." << std::endl;
        return *this;
    }

    Bulk_quote(Bulk_quote&& orig):Disc_quote(std::move(orig)){ //orig itself is a variable, it's lvalue
        max_qty = std::move(orig.max_qty);
        //make orig safe to destruct
        //orig.max_qty = 0;
        std::cout << "Bulk_quote move construct." << std::endl;
    }

    Bulk_quote& operator=(Bulk_quote&& rhs){
        if(this != &rhs){
            Disc_quote::operator=(std::move(rhs));//rhs itself is a variable, it's lvalue
            max_qty = std::move(rhs.max_qty);
            //make rhs safe to destruct
            //rhs.max_qty = 0;
        }
    
        std::cout << "Bulk_quote move assignment." << std::endl;
        return *this;
    }

    ~Bulk_quote(){
        std::cout << "Bulk_quote destructor called." << std::endl;
    }


private:
    //since we only decide max_qty strategy for Bulk_quote class, so max_qty be a member of B ulk_quote, not Disc_quote
    //cause there may be other strage inherit from Disc_quote that does not set limit on max_qty
    //basically, all strategy class at least have one qty setting, so that setting in abstract base class Disc_quote
    std::size_t max_qty = 0; //max quantity that can have discount 
};

#endif