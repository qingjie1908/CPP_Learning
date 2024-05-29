#include <string>
#include <memory>
#include <iostream>
#include <vector>

class HasPtr{
friend void swap(HasPtr& obj1, HasPtr& obj2);
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0){}

    //copy constructor decalaration
    HasPtr(const HasPtr&);

    //copy assignment operator decalartion
    //not passsing by referen cause we want to using swap 
    //also cannot be const
    HasPtr& operator=(HasPtr rhs);

    bool operator<(HasPtr& rhs);

    //destuctor declaration, it must have no return type and no parameter
    ~HasPtr();

    void check_ps() {std::cout << "ps is: " << ps << ", &i is: " << &i << std::endl;} //check member ps address value

    //move below delete to destructor part
    // void delete_ps() {delete ps; //after this, ps still hold string s, string memory freed, dangling pointer, dereference is disaster
    //     ps = nullptr; //change dangling pointer to nullptr
    // }
    std::string *ps;
    int i;
private:
    //std::string *ps;
    //int i;
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
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    //call =(); rhs using copy constructor to create a temp obj

    rhs.check_ps();
    using std::swap;
    swap(*this, rhs); //this will call own defined swap, not std::swap cause type matching better
    //after call, this.ps point to rhs memory
    //rhs.ps point to orignal lhs had
    //after =(); rhs destroyed, will call destructor to free the memory
    return *this;
}

bool HasPtr::operator<(HasPtr &rhs)
{
    if(i >= rhs.i)
        return false;
    else
        return true;

}

//destructor
HasPtr::~HasPtr(){
    delete ps; //hit count = 2, two object out of scope will call destructor func twice
    ps = nullptr; //this can be ignored since when obj out of scope, built-in pointer will be destroyed
}

void swap(HasPtr& obj1, HasPtr& obj2){

    //using std::swap;
    swap(obj1.ps, obj2.ps); //only change ps, use std::swap
    std::swap(obj1.i, obj2.i); //using std::swap, cause this swap type not match. will not call own decided swap
    std::cout << "own defined swap is called" << std::endl;
}



int main()
{
    HasPtr A("A"), B("B"), C("C"), D("D"), E("E"); 
    A.i = 4; B.i = 2; C.i = 2; D.i = 1; E.i = 0;

    std::vector<HasPtr> vec1 = {A, B, C, D, E};

    //before swap
    //&A: 0x000000016fdff200, ps is: 0x124605570, &i is: 0x16fdff208
    //&B: 0x000000016fdff1c8, ps is: 0x124605590, &i is: 0x16fdff1d0

    if (B < A){
        swap(A, B); //call own defined 
    }

    //After swap, so only member ps address change, A B two object address not change
    //&A: 0x000000016fdff200, ps is: 0x124605590, &i is: 0x16fdff208
    //&B: 0x000000016fdff1c8, ps is: 0x124605570, &i is: 0x16fdff1d0

    //note when construct vec1, use copy constructor, &vec1[0] and &A are not different

    //insertion sort
    for(size_t i = 1; i < vec1.size(); ++i){
        size_t start = i;
        while((i - 1 >= 0) && (vec1[i] < vec1[i-1])){
            swap(vec1[i], vec1[i-1]);
            --i;
        }
        i = start;
    }
    //after swap, &vec1[0] is unchange, its elemnent change to "E",0

    //auto item = vec1[0];
    for(auto item : vec1){
        std::cout << item.i << " ";
    }
    std::cout << std::endl;
    //output
    /*
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    own defined swap is called
    0 1 2 2 4
    */

}

