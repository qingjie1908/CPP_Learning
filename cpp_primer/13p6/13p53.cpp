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

    //move constructor
    HasPtr(HasPtr&& p) noexcept;

    //move assignment operator
    HasPtr& operator=(HasPtr&& rhs);

    //copy assignment operator decalartion
    //not passsing by referen cause we want to using swap to
    //also cannot be const
    //if rhs is non-reference paramenter, then when arugment is rvalue reference, HasPtr rhs = ref_rvalue, then it will call move constructor, which consume no new memory
    //when argument is lvalue, then it will call copy constructor, will involve new memory created, a kind of waste
    //if we define both copy assignment and move assignment use rhs prameter by reference, then no new memory created will be involved
    //HasPtr& operator=(HasPtr rhs);

    //copy assignment pass by reference,
    //if we use swap, paramenter rhs cannot be const, cause we need to change rhs.ps and rhs.i
    HasPtr& operator=(HasPtr& rhs);

    bool operator<(const HasPtr &rhs) const;

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
    std::cout << "copy constructor called" << std::endl;
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

//move constructor
HasPtr::HasPtr(HasPtr&& p) noexcept : ps(p.ps), i(p.i) {
    p.ps = 0;
    std::cout << "move constrcutor called" << std::endl;
}

//copy assignment operator by reference, not by non-reference (copy and swap)
HasPtr& HasPtr::operator=(HasPtr& rhs){
    swap(*this, rhs); //also consider self assignment, then nothing change
    std::cout << "copy assignment called" << std::endl;
    return *this;
}

//move assignent operator
HasPtr& HasPtr::operator=(HasPtr&& rhs){
    if(this != &rhs){
        swap(*this, rhs); //after =(), rhs hold lhs value,
        //since rhs is reference, when func end, rhs will not be destroyed, only when rhs referenced obj in main func out of scope, rhs pointed memory will be freed
        //or we can free rhs now
        delete rhs.ps;
        rhs.ps = nullptr;
        //then after rhs out of scope, call its destructor again, and it's ok to delete nullptr

    }
    //if lhs and rhs are the same obj, do nothing
    std::cout << "move assignment called" << std::endl;
    return *this;
}

/*
if rhs is non-reference paramenter, then when arugment is rvalue reference, HasPtr rhs = ref_rvalue, then it will call move constructor, which consume no new memory
when argument is lvalue, then it will call copy constructor, will involve new memory created, a kind of waste

if we define both copy assignment and move assignment use rhs prameter by reference, then no new memory created will be involved

//copy assignment operator also consider rhs and lhs are the same obj
HasPtr& HasPtr::operator=(HasPtr rhs)
{
    //call =(); rhs using copy constructor to create a temp obj

    using std::swap;
    swap(*this, rhs); //this will call own defined swap, not std::swap cause type matching better
    //also we cannot std::swap this = &rhs, because this is constant pointer
    //we can std::swap(this->ps, rhs->ps)

    //after call, this.ps point to rhs memory
    //rhs.ps point to orignal lhs had
    //after =(); rhs destroyed, will call destructor to free the memory

    //first this = 0x1; temp obj &rhs = 0x2
    //after swap, this=0x2; temp pbj &rhs = 0x1;
    //not only change member element value; but also change the the whole obj
    //its like value like verion does not change &(*this), which is "this", it just change this.ps
    //pointer like veriosn, change "this" value

    std::cout << "copy assignment operator called" << std::endl;
    //after swap, rhs obj destroyed
    return *this;
}
*/

//operator should use const paramenter, cause we do not want to change it
//also it should add const as const member function
//const member func can be called with both non-const and const object
//for our insertion sort, it called on non-const vec1[i];

//but std::sort() use const obj as paramenter for its predicate
//like [](const HasPtr& obj1, const HasPtr& obj2)->bool{return (obj1 < obj2);
//so fisrt, the parameter for <() func should be const
//second, it should add const at last indicate const member function
bool HasPtr::operator<(const HasPtr &rhs) const
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
    std::cout << "destructor called" << std::endl;
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

    std::vector<HasPtr> vec1 = {A, B, C, D, E}; //copy constructor call

    A.check_ps();
    B.check_ps();
    //before swap
    //&A: 0x000000016fdff1f0, ps is: 0x146904080, &i is: 0x16fdff1f8
    //&B: 0x000000016fdff1b8, ps is: 0x146a04080, &i is: 0x16fdff1c0

    if (B < A){
        swap(A, B); //call own defined 
    }
    A.check_ps();
    B.check_ps();

    //After swap, so only member ps address change, A B two object address not change
    //&A: 0x000000016fdff1f0, ps is: 0x146a04080, &i is: 0x16fdff1f8
    //&B: 0x000000016fdff1b8, ps is: 0x146904080, &i is: 0x16fdff1c0

    //note when construct vec1, use copy constructor, &vec1[0] and &A are different

    //insertion sort, {4,2,2,1,0}, total swap 9 times
    for(size_t i = 1; i < vec1.size(); ++i){
        size_t start = i;
        while((i - 1 >= 0) && (vec1[i] < vec1[i-1])){
            swap(vec1[i], vec1[i-1]);
            --i;
        }
        i = start;
    }
    //after swap, &vec1[0] is unchange, its elemnent change to "E",0, called 10 times own defined swap

    //std::sort(vec1.begin(), vec1.end(), [](const HasPtr& obj1, const HasPtr& obj2)->bool{return (obj1 < obj2);});
    //use copy constructor for obj1, obj2
    //called own defined swap 19 times;

    //std::sort(vec1.begin(), vec1.end()); //same as last sort, since we provide operator< func

    //auto item = vec1[0];
    for(auto item : vec1){
        std::cout << item.i << " ";
    }
    std::cout << std::endl;
    //output, 0 1 2 2 4, correct, each item will call destructor each loop
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
    0 destructor called  
    copy constructor called
    1 destructor called
    copy constructor called
    2 destructor called
    copy constructor called
    2 destructor called
    copy constructor called
    4 destructor called
    */

    E.check_ps(); //&E: 0x000000016fdff140, ps is: 0x121605fa0, &i is: 0x16fdff148
    HasPtr F(std::move(E)); //move constructor; not use E anymore, and move constructor will set E.ps to nullptr
    E.check_ps(); //&E: 0x000000016fdff140, ps is: 0x0, &i is: 0x16fdff148
    F.check_ps(); //&F: 0x000000016fdff0b0, ps is: 0x121605fa0, &i is: 0x16fdff0b8 (&i is different, cause use value copy initialized)

    D.check_ps(); //&D: 0x000000016fdff168, ps is: 0x121605f80, &i is: 0x16fdff170
    F = std::move(D); //move assignment; not use D anymore
    //ex 13.54 if define HasPtr& operator=(HasPtr& rhs); HasPtr& operator=(HasPtr&& rhs); then obj1 = std::move(obj2); will call move assignment
    //if define HasPtr& operator=(HasPtr rhs); HasPtr& operator=(HasPtr&& rhs); then obj1 = std::move(obj2);  error
    //error is more than one operator “=“ matches, cause it can call both copy and move assignment version, 
    //cause it can first call move constructor construc rhs // then call the copy assignment version
    //or it can directly use the move assignment version, pass std::move(D) by rvalue reference to rhs, instread of construct rhs;


    F.check_ps(); //&F: 0x000000016fdff0b0, ps is: 0x121605f80, &i is: 0x16fdff0b8 , now F hold D original ps value
    D.check_ps(); //&D: 0x000000016fdff168, ps is: 0x0, &i is: 0x16fdff170 , now D hold F original ps, then in move assignement, delete this ps, then point to nullptr
    /*
    ps is: 0x121605fa0, &i is: 0x16fdff148
    move constrcutor called
    ps is: 0x0, &i is: 0x16fdff148
    ps is: 0x121605fa0, &i is: 0x16fdff0b8
    ps is: 0x121605f80, &i is: 0x16fdff170
    ps is: 0x121605fa0, &i is: 0x16fdff0b8
    own defined swap is called
    move assignment called
    ps is: 0x121605f80, &i is: 0x16fdff0b8
    ps is: 0x0, &i is: 0x16fdff170
    11x destructor called (A,B,C,D,E,F plus five elements in vector)
    */

}