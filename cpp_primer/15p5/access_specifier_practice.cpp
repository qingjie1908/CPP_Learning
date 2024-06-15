//access specifier used in a derivation list
//determines whether users of a derived class are allowed to know that the derived class inherits from its base class.
// derivation is public, the public members of the base class become part of the interface of the derived class object as well
//so for class Bulk_quote : public Quote, Bulk_quote obj_derived, obj_derived.isbn() and print_total(std::cout, obj_derived, 10) is ok
//if class Bulk_quote : private Quote,  Bulk_quote obj_derived, obj_derived.isbn() and print_total(std::cout, obj_derived, 10) is illegal, only obj_derived.net_price() is ok

//but note, even class Bulk_quote : private Quote
//inside Quote class, we can still call like std::stirng ss = isbn();
//its like, when we defind class Bulk_Quote, the class Bulk_Quote itself is the user of Quote
//so in Bulk_Quote class body defination, whether it can use isbn() or price or bookNo depends on whether these member/func are public/protected in class Quote or private in class Quote
//so in class Bulk_quote : private Quote{}, std::string ss = this->isbn(); double dd = price; is ok, since they are public/protected in class Quote, ss = bookNo; is illegal, since it's private in class Quote

//when we define Bulk_Quote obj_derived; obj_derived is the user of derived Bulk_quote class, not Quote class
//so obj_derived.net_price() is ok,
//printe_total(obj_derived) and obj_derived.isbn() is ok or not depend on the access specifier in derivation list
//so public in derivation list is key to dynamic binding, if its private, then you cannot bind a Derived_obj to a Base type reference, cause the Base member even public is not seen by this derived obj

//so user "class Bulk_quote" of "class Quote" can access which in base depend on the access specifier inside base class "Quote"
//user obj_derived (object of Bulk_quote or derived-class of Bulk_quote) of "class Bulk_quote" can access which in base depend on the access specifier inside "class Bulk_Quote",
//obj_derived whether can access base class public member and be treated as base class object, depends on the access specifier in the derivation list
//if derivation list is protected, then public member of Base would be protected member in Bulk_quote
//if class next_derived_class : public Derived; then next_derived_class can access these protect member in Bulk_quote,
//object of type next_derived_class

//When the derivation is public, the public members of the base class become part of the interface of the derived class as well. 
//In addition, we can bind an object of a publicly derived type to a pointer or reference to the base type. key for dynamic binding

#include <iostream>


class Base{
friend class Pal;
public:
    int base_pub;

private:
    int base_pri;

protected:
    int base_pro;
};

class Derived : public Base{
friend void func1(Base& bobj);
friend void func2(Derived& dobj);
public:
    int deri_pub;
    void func3() {base_pro = 1; base_pub = 1;} //can access, but usaually should only read, not assgin base member
private:
    int deri_pri;
protected:
    int deri_pro;
};

//here user of "class Derived" is "class next_Derived", it is not an object, but a class
//so it can access "class Derived" public and protected member
//if class Derived : public Base, then it can be see public member in Base is still public in Derived
                            //protected member in Base is still protected in Derived
                            //so user of "class Derived" can access Base public, if user is a class, then it can also access Base protected

//if class Derived : protected Base, then it can be see public member in Base becomes proteced in Derived,
                            //protected member in Base is still protected in Derived
                            //so user of "class Derived" if its an object, then can not access Base public, also cannot access Base protected
                            // if user is a class, like "class next_Derived", then it can access Base public, and can also access Base protected

//if class Derived : private Base, then all member in Base become private in class Derived, 
                    //"class next_derived" cannot access any member in base
class next_Derived : public Derived{
    int a = deri_pub; //ok
    int b = deri_pro; //ok
    int c = deri_pri; //error
    int d = base_pub; //ok if class Derived : public Base, or class Derived : protected Base
    //error if class Derived : private Base
    int e = base_pro; //ok if class Derived : public Base, or class Derived : protected Base
    //error if class Derived : private Base
};

next_Derived objj;
int aaa = objj.base_pub;

//class Derived itself has access to itself all member, and Base class base_pro, base_pub, but generally should not assign them, just read them
//friend func1 of class Derived has same access level as Derived, so Derived all member, and Base public and protected
//but these access should be thorugh a Derived obj, since friend func1 is Derived friend func, not Base class friend func
void func1(Base& bobj){ //friend of class Derived
    Derived dobj_func1;
    dobj_func1.deri_pub = 1;
    dobj_func1.deri_pri = 2;
    dobj_func1.base_pub = 1;
    dobj_func1.base_pro = 1;
    dobj_func1.deri_pro = 1;

    Base bobj_func1;
    bobj_func1.base_pub; 
    bobj_func1.base_pro; //error, static and dynamic type are Base, can only access public as a object user

    bobj.base_pub;
    bobj.base_pro; //not allowed, no matter this reference dynamic type is Base or Derived, dynamic bunding only for virtual function, not for data member
    //if this allowed, then when bobj.base_pro is error in main func, we can pass it into freind func1 to alter this error, which is not resonable, then the protected in base has no meaning

}

void func2(Derived& dobj){ //friend of class Derived, also note no base to derive conversion
    Derived dobj_func2;
    dobj_func2.deri_pub;
    dobj_func2.deri_pri;
    dobj_func2.deri_pro;
    dobj_func2.base_pub;
    dobj_func2.base_pro;

    Base bobj_func2;
    bobj_func2.base_pub;
    bobj_func2.base_pro; //error

    //no Base to Derived conversion !!!, here reference is Derived&
    dobj.deri_pub;
    dobj.deri_pri;
    dobj.deri_pro;
    dobj.base_pub;
    dobj.base_pro;
}

void func3(Base& bobj){ //not friend
    Derived dobj_func3;
    dobj_func3.deri_pub; //func3 no friend of class derived, so obj_func3 only access deri_pub
    dobj_func3.base_pub; //if derivation list public, ok, if private, error

    Base bobj_func3;
    bobj_func3.base_pub; //only access this

    //bobj is reference to base, although dynamic type can be derived, but this only comes to consideration for virtual member function
    bobj.base_pub; //only access this
    bobj.base_pro;
    
}



void func4(Derived& dobj){ //not friend, also note no base to derive conversion
    Derived dobj_func4;
    dobj_func4.deri_pub;
    dobj_func4.base_pub; //if derivation list public, ok, if private, error

    Base bobj_func4;
    bobj_func4.base_pub; //only access this

    dobj.deri_pub;
    dobj.base_pub; //if derivation list public, ok, if private, error
}

class Pal {
    Derived obj;
    int a = obj.deri_pub;
    int b = obj.deri_pri; //error, Pal not friend of Derived

    //c d e is suprise
    //if in main func or other scope, c is allowed only class Derived : public Base, d, e not allowd
    //but here it access base_pri and base_pro inside class Pal
    //and class Pal is a friend class of class Base
    //so inside class Pal, its data member and member func can access Base objects all member
    //no matter this base object is a base type, or is a part that embedded in an object of derived type
    int c = obj.base_pub; 
    int d = obj.base_pri;
    int e = obj.base_pro;

    Base bobj;
    int aa = bobj.base_pub;
    int bb = bobj.base_pri;
    int cc = bobj.base_pro;

    int func(Derived obj) {return obj.base_pub;}

    
     //this is ok even if class Derived : private base
    //because class Pal is friend class of Base
    //inside class pal, its data member or member func can access the Base objects
    //or the Base object is embedded in an derived_class object
};


int main()
{

    Derived dobj1; Base bobj1;
    func1(dobj1);
    func1(bobj1);

    Derived dobj2; Base bobj2;
    func2(dobj2);
    func2(bobj2); //always wrong no matter drivation list public or private, cause no base to derive conversion

    Derived dobj3; Base bobj3;
    func3(bobj3);
    func3(dobj3); //if derivation list is public, ok, private, error
    
    Derived dobj4; Base bobj4;
    func4(bobj4); //always wrong no matter drivation list public or private, cause no base to derive conversion
    func4(dobj4);
}