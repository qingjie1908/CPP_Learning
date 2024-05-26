//ex 13.11

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

    void check_ps() {std::cout << "ps is: " << ps << std::endl;} //check member ps address value

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
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    *ps = *rhs.ps; // copy pointed value, not memory address
    i = rhs.i;

    //assignment operator return reference to lhs operand
    //lhs operand is *this
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
        second.check_ps(); //0x141605f60
    }
    //out of scope, second and orig will call its destructor

}