#include <iostream>

class Base{
public:
    virtual int fcn(){return 1;}
};

class D1 : public Base {
public:
    int fcn(int) {return 11;}
    virtual void f2() {std::cout << "D1::f2()" << std::endl;}
    using Base::fcn; //add this, is just like explicity add below code:
    //int fcn() override {return 123;} // if without this, virtual fcn() will be hidden by D1::fcn()
    //if add this so both fcn() and virtual fcn(int) can be seen in the same scope inside D1 when name look up happens
    //otherwise fcn() is inside scope D1, virtual Base::fcn(int) is in Base scope, which is the outer scope comapred to D1
    //note if we overried this in D1, p_D1->fcn() will get 123, but (*p_D1).Base::fcn() will still get 1
    //if using Base::fcn, then p_D1->fcn() get 1
    //if using Base::fcn and fcn() override both exists in D1, then p_D1->fcn() get 123

    //note: using just add scope into this class, does not affect inheritence, 
    //virtual int Base::fcn(){return 1;} is still inherited, but just in outer scope when no using, affect name look up

};

class D2 : public D1 {
public:
    int fcn(int) {return 111;}
    int fcn() override {return 222;}
    void f2() override {std::cout << "D2::f2()" << std::endl;}
};

int main()
{
    D1* p_D1;
    D1 obj_d1;
    p_D1 = &obj_d1;

    //if not "using fcn" in Base class
    //p_D1->fcn() will be error, cause Name look up before type checking
    //first look p_D1 static type, which is class D1, find name fcn, yes, then stop search fcn (currently virtual Base::fcn is in outer scope, in class Base, fcn() is in inner scope class D)
    //so Base::virtual int fcn() is hidden by D1::fcn(int)
    //now check type, in D1, int fcn(int), here not pass int argument, error
    int a1 = p_D1->fcn(); //error if no using Base::fcn or not explicitly override virtual Base::fcn(int)
    int a2 = (*p_D1).Base::fcn(); //ok, 1
    int b = p_D1->fcn(1); //correct, b is 11

    //if add "using Base::fcn" in Derived class, all "fcn" func (including non-virtual) in outer scope Base will be added to inner scope D1
    //for virtual function, its like we expilcitly add: int fcn() override {return 1;} in class D1, although not change function body, now its in same scope with D1::fcn()
    //for non-vritual function, its like we explicty add same functions in class D1, also in same scope with D1
    //so when first look p_D1 static type, there are two names fcn, one is D1::fcn(int), another is Base::fcn()
    //then for type check, it will decide which call to bind
    int a3 = p_D1->fcn(); //will be correct, call Base::fcn(), 1




}