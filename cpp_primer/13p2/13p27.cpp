#include <string>
#include <memory>
#include <iostream>

class HasPtr{
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0){ use_count = new std::size_t(1);} //use dynamic memory for use_count

    //copy constructor decalaration
    HasPtr(const HasPtr&);

    //copy assignment operator decalartion
    HasPtr& operator=(const HasPtr& rhs);

    //destuctor declaration, it must have no return type and no parameter
    ~HasPtr();

    void check_ps() {std::cout << "ps is: " << ps << ", &i is: " << &i 
                        << ", ps.use_count is: " << *use_count << std::endl;} //check member ps address value

    //move below delete to destructor part
    // void delete_ps() {delete ps; //after this, ps still hold string s, string memory freed, dangling pointer, dereference is disaster
    //     ps = nullptr; //change dangling pointer to nullptr
    // }
private:
    std::string *ps;
    int i;
    std::size_t* use_count;
};

//copy constructor defination


HasPtr::HasPtr(const HasPtr& orig){
    i = orig.i;

    //pointer copy, object has one more user
    ps = orig.ps;
    ++*orig.use_count; //add 1 more user

    //then copy use count
    use_count = orig.use_count; //now both intialized obj and orig has same incremented use_count

}

//copy assignment operator definantion, always return reference to lhs operand for = operator
//copy assignment operator also consider rhs and lhs are the same obj
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
    //first, increment the use count of rhs, in case self assignment the lhs is not freed if lhs.obj has only 1 user 
    ++*rhs.use_count;

    //now, decrement the use count of lhs
    --*use_count;

    //check if lhs's dynamic memory needed freed
    if(*use_count == 0){
        delete ps; //freed lhs orinal memory
        delete use_count; //also free use_count corresponding to original memory
    }

    ps = rhs.ps; //lhs now ponit to same memory as rhs
    i = rhs.i;
    use_count = rhs.use_count; //use count now responds for new memory

    return *this;
}

//destructor
HasPtr::~HasPtr(){
    //if an obj go out of scope
    //obj destoyed, inside obj's dynamic memory part not delete yet
    //check first if that memory only has this one obj user

    //fist --use_count
    --*use_count;

    if(use_count == 0){ //obj is the last user
        delete ps;
        delete use_count;
    }
}

int main()
{
    {//innner scope
        HasPtr orig("hello"); //direct initialization, use default constructor
        HasPtr second = orig; //initialization, use copy constructor

        orig.check_ps(); //ps is: 0x139204080, &i is: 0x16fdff260, ps.use_count is: 2
        second.check_ps(); //ps is: 0x139204080, &i is: 0x16fdff220, ps.use_count is: 2

        second = orig; //assignment, use copy assignment operator function

        orig.check_ps(); //ps is: 0x139204080, &i is: 0x16fdff260, ps.use_count is: 2
        second.check_ps(); //ps is: 0x139204080, &i is: 0x16fdff220, ps.use_count is: 2

        HasPtr obj4("aa");
        obj4.check_ps(); //ps is: 0x139304080, &i is: 0x16fdff208, ps.use_count is: 1
        obj4 = obj4; //self assign
        obj4.check_ps(); //ps is: 0x139304080, &i is: 0x16fdff208, ps.use_count is: 1

        obj4 = second;
        obj4.check_ps();//ps is: 0x139204080, &i is: 0x16fdff208, ps.use_count is: 3; ps change, original obj4 ps deleted, original obj4 count deleted
        orig.check_ps();//ps is: 0x139204080, &i is: 0x16fdff260, ps.use_count is: 3
        second.check_ps(); //ps is: 0x139204080, &i is: 0x16fdff220, ps.use_count is: 3

        //note orig, second, obj4 's member int i has different address
    }
    //out of scope, second and orig will call its destructor

}