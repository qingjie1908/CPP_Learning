//ex 13.5

#include <string>
#include <memory>
#include <iostream>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0){}

    //copy constructor decalaration
    HasPtr(const HasPtr&);

    void check_ps() {std::cout << ps << std::endl;} //check member ps address value
    void delete_ps() {delete ps; //after this, ps still hold string s, string memory freed, dangling pointer, dereference is disaster
        ps = nullptr; //change dangling pointer to nullptr
    }
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

int main()
{
    HasPtr orig("hello");
    HasPtr second = orig;

    orig.check_ps(); //0x141605f40
    second.check_ps(); //0x141605f60

    //class has dynamic memory initialized from new
    orig.delete_ps();
    second.delete_ps();

    //check again, 
    orig.check_ps(); //0x0
    second.check_ps(); //0x0

    return 0;
}