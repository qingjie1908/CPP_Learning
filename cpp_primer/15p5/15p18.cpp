#include <iostream>

class Base {
public:
    void pub_mem(){std::cout << "Hello from Base." << std::endl;}
    void memfcn(Base& b) {b = *this;} //this will call default systhesized Base& Base::opeartor=(const Base& rhs);
    //member wise copy for default synthesized
    //prot_mem = rhs.prot_mem;
    //priv_mem = rhs.priv_mem;
    //here rhs is (*this), a Base type object or any derived type
    
    //note, Base& Base::opeartor=(const Base& rhs);
    //rhs can be Base type or any other type, its just use the Base object part embedded in anyother type

    //inside class Base or any other class that is Base'friend
    //its data member and member func can access Base part (private, public and protected) through Base or Derived object
    int pub_member = 2;
protected:
    int prot_mem = 1;
private:
    char priv_mem = 'a';
};

struct Pub_Derv : public Base {
    int f() {return prot_mem;}
    void memfcn(Base& b){b = *this;} 
    //this member func want to access Base part, ok, copy assignment of Base is public
    //Base bobj; in this class also ok cause it can access and obj.public, obj.prive and obj.prot by nature can not be accessed
    //this will call default systhesized void Base::opeartor=(const Base& rhs);
    //member wise copy
    //b.prot_mem = rhs.prot_mem;
    //b.priv_mem = rhs.priv_mem;
    //here rhs is (*this), an object of type Pub_Derv;
    //systhesized void Base::opeartor=(const Base& rhs); will only copy the Base class part

};

struct Priv_Derv : private Base{
    int f1() const {return prot_mem;}
    void memfcn(Base& b){b = *this;}
    //this func want to access Base part, ok
    //cause user is class "Priv_Derv",
    //this can access prot mem;
    //bobj.prot and bobj.priv is not allowed by nature since user is bobj;
    Base bobj; //ok
    int func(){bobj.pub_mem(); return prot_mem;} //ok
    int a = prot_mem; //ok
    //copy assignment of Base is public, so b = *this; ok


};


struct Prot_Derv : protected Base {
    //public member in Base become protected  in this class
    //protecte member in Base become protected in this class
    //private member in Base become private in this class
    void memfcn(Base& b){b = *this;}

    
};

struct Derived_from_Public : public Pub_Derv{
    //ok:Base::prot_mem remains protected in Pub_Derv
    //Base::public remains public in Pub_Derv
    int use_base() {return prot_mem;}
    void memfcn(Base& b){b = *this;}
    Base bobj;
    int a = bobj.pub_member;
    char aa = bobj.prot_mem;
    Pub_Derv dobj;
    int b = dobj.pub_member;
    char bb = dobj.prot_mem;
};

struct Derived_from_Private : public Priv_Derv{
    //error:Base::prot_mem is private in Priv_Derv
    //int use_base() {return prot_mem;}
    //public member in Priv_Derv is public in this class
    //private member in Priv_Derv is private in this class
    //protected member in Priv_Derv is protected in this class

    //now this "struct Derived_from_Private" is user, its a class kind user, not an object kind user
    //so it can acess direct base class, which is Priv_Derv's public and protected part
    //in Priv_Derv, all Base part are inheritied as its private part cause its privated inherited from Base
    //so in struct Derived_from_Private, we can access Priv_Derv's public and protected part, but not its private part in which the Base part is also in it
    Base bobj; //so this is error cause all Base part is private in its direct base class "Priv_Derv"
    //when you create bobj, user is "struct  Derived_from_Protected", since all Base part is inaccessible for "struct Derived_from_Private", so user "struct Derived_from_Private" cannot create an Base obj
    void memfcn(Base& b){b = *this;} //also error cuase base part not available for user "struct Derived_from_Private"
    int a = f1(); //ok, f1 is Public part in Priv_Derv
    Priv_Derv dobj;
    int b = dobj.a;
    int bb = dobj.pub_member;
};


struct  Derived_from_Protected : public Prot_Derv{
    //public member in Prot_Derv become public in this class
    //private member in Prot_Derv become private in this class
    //protected member in Prot_Derv becom protected in this class
    void memfcn(Base& b){b = *this;}
    Base bobj; //ok, cuase public and protected part of Base are all protected part in Prot_Derv
    //when you create bobj, user is "struct  Derived_from_Protected", so can create Base bobj;
    //Base copy assignment operator become protected in Prot_Derv, user "struct  Derived_from_Protected" can also access it

    int a = bobj.pub_member; //now user is bobj, can only access bobj.pub_member

    int b = pub_member; //it's this.pub_member, not bobj.pub_member
    //this pub_member is inherited from Base class, you can think it's in an unname Base object part in this struct  Derived_from_Protected

    int c = prot_mem; //it's this.prot_mem, user is "struct  Derived_from_Protected"
};




int main()
{
    Base bobj;
    Pub_Derv d1;
    Priv_Derv d2;
    Prot_Derv d3;
    Derived_from_Public dd1;
    Derived_from_Private dd2;
    Derived_from_Protected dd3;

    Base* p =  &d1; //p static type is Base*, we can only use p to access the Base_object part embeded in the Derived Obj
    
    //here user is not class, but object *p;
    // p = &d2; //error, intend use p to access Base::pub_mem(), but pub_mem become private member in class Priv_Derv
    // p = &d3; //error, intend use p to access Base::pub_mem(), but pub_mem become protected member in class Priv_Derv

    // p = &dd1; //ok, intend use p to access Base::pub_mem(), this is public in Pub_Derv, and Public in Derived_from_Public
    // p->pub_mem(); //ok

    // p = &dd2; //error,  Base::pub_mem() is private in class Derived_from_Private

    // p = &dd3; //error,  Base::pub_mem() is protected in class Derived_from_Protected

    d1.memfcn(bobj); //ok
    d2.memfcn(bobj); //ok
    d3.memfcn(bobj); //ok
    dd1.memfcn(bobj); //ok
    dd2.memfcn(bobj); //ok
    dd3.memfcn(bobj); //ok
    //all ok because thye final call Base& Base::opeartor=(const Base& rhs); only copy the Base part
    //and Base& Base::opeartor=(const Base& rhs); is member func of class Base, can access Base part all member, public, private, protected
    

}
