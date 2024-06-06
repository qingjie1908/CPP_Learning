#include <iostream>
#include <vector>
#include <algorithm> //for std::sort

class Foo{
public:
    Foo():data(std::vector<int>()){} //default data to empty vec
    Foo(const Foo& orig); //copy constructor
    Foo& operator=(const Foo& rhs);
    Foo(std::vector<int> vec):data(vec){std::cout << "use vector construct Foo" << std::endl;} //constructor take a vec, call std::vector<int> copy constructor

    //member func
    Foo sorted() &&; //may run on omdifiable rvalues
    Foo sorted() const &; //may run on any kind of Foo

    std::vector<int> data;

private:
    //std::vector<int> data;
};

Foo::Foo(const Foo& orig){
    data = orig.data; //this will use std::vector<int> copy constructor
    std::cout << "use Foo copy constuct" << std::endl;
}

Foo& Foo::operator=(const Foo& rhs){
    data = rhs.data;
    std::cout << "use copy assignment" << std::endl;
    return *this;
}

Foo Foo::sorted() && { //'this' obj is modifiable rvalue
    std::sort(data.begin(), data.end());
    std::cout << "rvalue version sorted called" << std::endl;
    return *this;
}

Foo Foo::sorted() const &{ //'this' obj is any kind of Foo
    //const we cannot change 'this' it self
    //first copy construct
    //Foo ret(*this); //cout use Foo copy constuct
    //std::sort(ret.data.begin(), ret.data.end());
    std::cout << "const reference version sorted called" << std::endl;
    //return ret;

    return Foo(*this).sorted();
}

Foo func(){
    return Foo({9,5,6}); // use vector construct Foo
}

int main()
{
    Foo obj1(std::vector<int>{3, 1, 5, 4}); //list initialize vec, //then cout: use vector construct Foo
    //obj1.sorted(); &obj1 0x220
    //check obj1, not change, //cout: use Foo copy constuct, const reference version sorted called

    Foo(obj1).sorted();
    //Foo(obj1) called copy constructor, but not used to initialize an object, so Foo(obj1).sorted(); will call && rvalue version sorted() on temp_obj1
    //when rvalue sorted called, it will return temp_obj1 as a new temp Foo,
    //so copy constructor will be called again to construct a new temp_obj2 (rvalue cause return type is non-reference) from temp_obj1
    //after this step, temp_obj2 destructor will be called first, then temp_obj1 destructor will be called

    Foo obj2(obj1.sorted()); // &obj2 0x1d0
    //check obj2, sorted data, obj1 not changed, //cout: use Foo copy constuct, const reference version sorted called

    Foo&& r_ref_obj3 = obj1.sorted(); //obj3 itself is an object, lvalue, a reference to rvalue //const reference version sorted called
    r_ref_obj3.data = {7, 6, 5};
    r_ref_obj3.sorted(); //const reference version sorted called, r_ref_obj3 it self not changed
    //check r_ref_obj3;

    Foo obj4(func().sorted()); //rvalue version sorted called
    //use Foo copy constuct, obj4 is 5,6,9

}