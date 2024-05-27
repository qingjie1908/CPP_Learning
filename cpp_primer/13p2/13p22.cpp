#include <string>
#include <memory>
#include <iostream>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0){}

    //copy constructor decalaration
    HasPtr(const HasPtr&);

    //copy assignment operator decalartion
    HasPtr& operator=(const HasPtr& rhs);

    //destuctor declaration, it must have no return type and no parameter
    ~HasPtr();

    void check_ps() {std::cout << "ps is: " << ps << ", &i is: " << &i << std::endl;} //check member ps address value

    //move below delete to destructor part
    // void delete_ps() {delete ps; //after this, ps still hold string s, string memory freed, dangling pointer, dereference is disaster
    //     ps = nullptr; //change dangling pointer to nullptr
    // }
private:
    std::string *ps;
    int i;
};

//copy constructor defination


HasPtr::HasPtr(const HasPtr& orig){
    i = orig.i;
    ps = new std::string(); //ps point to dynamic memory hold empty string
    
    //ps = orig.ps; wrong, it should not copy address, but copy pointed string value
    *ps = *orig.ps;
}

//copy assignment operator definantion, always return reference to lhs operand for = operator
//note below code only do value copy when lhs and rhs are different obj
//we should also consider lhs and rhs are the same obj
//if they are the same object, below code are not doing value copied, but pointer copy, since after obj1 = obj1
//new obj1 sitll hold the same ps address
/*
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    *ps = *rhs.ps; // copy pointed value, not memory address
    i = rhs.i;

    //assignment operator return reference to lhs operand
    //lhs operand is *this
    return *this;
}
*/

//copy assignment operator also consider rhs and lhs are the same obj
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    auto p_temp = new std::string(*rhs.ps);

    delete ps; //free the old memory lhs ps has

    ps = p_temp;

    i = rhs.i;

    return *this;
}

//destructor
HasPtr::~HasPtr(){
    delete ps; //hit count = 2, two object out of scope will call destructor func twice
    ps = nullptr; //this can be ignored since when obj out of scope, built-in pointer will be destroyed
}

int main()
{
    {//innner scope
        HasPtr orig("hello"); //direct initialization, use default constructor
        HasPtr second = orig; //initialization, use copy constructor

        orig.check_ps(); //0x141605f40
        second.check_ps(); //0x141605f60

        second = orig; //assignment, use copy assignment operator function

        orig.check_ps(); //0x141605f40
        second.check_ps(); //0x141605fc0, assignment = change pointer address, value copy

        HasPtr obj4("aa");
        obj4.check_ps(); //ps is 0xa0, &i is 0xf220
        obj4 = obj4; //self assign
        obj4.check_ps(); //ps is 0x80, &i is still 0xf220, obj4 address updated, value copy, not pointer copy
    }
    //out of scope, second and orig will call its destructor

}