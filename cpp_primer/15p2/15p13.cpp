#include <string>
#include <iostream>


class base {
public:
    std::string name() { return basename; }
    virtual void print(std::ostream &os) { os << basename << std::endl; } 
private:
    std::string basename = "base";
};

class derived : public base { 
public:
    //void print(std::ostream &os) { print(os); os << " " << i; } //no scope operator, call this.print(os), which is derived version, dead loop
    //should be base::print(os)
    void print(std::ostream &os) { base::print(os); os << " " << i << std::endl; }
    std::string name() { return "derived name()"; }
private:
    int i = 33; 
};

int main()
{
    base obj_base;
    derived obj_derived;

    obj_base.print(std::cout);
    obj_derived.print(std::cout);

    base bobj; base* bp1 = &bobj; base& br1 = bobj;
    derived dobj; base* bp2 = &dobj; base &br2 = dobj;

    bobj.print(std::cout); //base
    dobj.print(std::cout); //base 33
    std::cout << bp1->name() << std::endl; //base
    std::cout << bp2->name() << std::endl; //non-virtual func, bind at compile-time, output "base"
    br1.print(std::cout); // base
    br2.print(std::cout); //base 33
    return 0;
}