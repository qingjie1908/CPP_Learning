#include <vector>
#include <string>
#include <iostream>
#include <memory>

struct X
{
    X() {std::cout << "X() default constructor called" << std::endl;}
    X(const X& orig){std::cout << "X(const X& orig) copy constructor called" << std::endl;}
    X& operator=(const X& rhs){std::cout << "copy assignment operator called" << std::endl; return *this;}
    ~X() {std::cout << "~X() destructor called" << std::endl; delete p2;} //p2 is directly dynamic allocated by new, need delete on our own

    int x = 0;
    std::string s = "hello";
    int *p1 = &x;
    int *p2 = new int(10);
    std::shared_ptr<std::string> ps = std::make_shared<std::string>("this");


};

void pass_as_nonref(X obj){};

void pass_as_ref(X& obj){};


/*
int main()
{
    //first only defalut initialize obj1
    X obj1;

    //output
    //X() default constructor called
    //~X() destructor called

}
*/

/*
int main()
{
    //second use copy constructor
    X obj1;
    X obj2(obj1);

    //output
    // X() default constructor called
    // X(const X& orig) copy constructor called
    // ~X() destructor called
    // ~X() destructor called
}
*/

/*
int main()
{
    //pass to func by reference
    X obj1;
    pass_as_ref(obj1);

    //output
    //X() default constructor called
    //~X() destructor called

}
*/

/*
int main()
{
    //pass as non reference
    X obj1;
    pass_as_nonref(obj1);
    //output
    // X() default constructor called // for obj1
    // X(const X& orig) copy constructor called // for temp obj in func
    // ~X() destructor called
    // ~X() destructor called

}
*/

/*
int main()
{
    X* p_x = new X;

    //if no delte p_x; output only has X() default constructor called, this constructs the obj in the dynamic memory
    //when out of scope, pointer p_x destroyed, but obj still exist
    //destructor not called if no delete p_x

    delete p_x; //when out of scope, p_x pointer destoyed, but memory not freed, need delete
    //when call delte, it freed the obj in the memory, so it will call the obj destructor
    
    p_x = nullptr;

    //output
    // X() default constructor called
    // ~X() destructor called

}
*/

/*
int main()
{
    X arr[3];

    //output
    // X() default constructor called
    // X() default constructor called
    // X() default constructor called
    // ~X() destructor called
    // ~X() destructor called
    // ~X() destructor called
}
*/

/*
int main()
{
    X* p = new X[3]; //p point to X[0]

    //if no delete p[]
    //output only has 3 times default constructor called for each element
    //each element is a dynamic obj, 
    //when out of scope, pointer p destroyed but dynamic object not destroyed

    //need delete p[] to free the dynamic obj memeory
    delete [] p; //these will call destructor on dynamic obj
    //output
    // X() default constructor called
    // X() default constructor called
    // X() default constructor called
    // ~X() destructor called
    // ~X() destructor called
    // ~X() destructor called
}
*/

/*
int main()
{
    std::vector<X> vec(3);
    //output
    
    X() default constructor called
    X() default constructor called
    X() default constructor called
    ~X() destructor called
    ~X() destructor called
    ~X() destructor called
    
}
*/

/*
int main()
{
    std::vector<X>* p = new std::vector<X>(3);
    //output
    // X() default constructor called
    // X() default constructor called
    // X() default constructor called
}
*/

int main()
{
    std::vector<X>* p = new std::vector<X>(3);
    delete p;
    //output
    // X() default constructor called
    // X() default constructor called
    // X() default constructor called
    // ~X() destructor called
    // ~X() destructor called
    // ~X() destructor called
}