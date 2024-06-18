#include <numbers> //for pi
#include <iostream>
class Geometric_primitive{
public:
    virtual ~Geometric_primitive() = default; //base class always has virtual destructor, even they do nothing
    void print() {
        std::cout << "Perimeters: " << get_perimeters() << ", Areas: " << get_areas() << std::endl;
    }
private:
    virtual double get_perimeters() const = 0; //pure virtual function
    //this class has pure virtual method, is abstract class, cannot use it to consturct a Geometric_primitive obj

    virtual double get_areas() const = 0;

};

class circle : public Geometric_primitive{
public:
    circle(double rp = 0):r(rp){}

protected:
    double r; //radius

private:
    double get_perimeters() const override {return std::numbers::pi * r * 2;}
    double get_areas() const override {return std::numbers::pi * r * r;}
};

class sphere : public circle{
public:
    sphere(double rp = 0):circle(rp){}

private:
    double get_perimeters() const override {return std::numbers::pi * r * 2;}
    double get_areas() const override {return std::numbers::pi * r * r * 4;}
};

class cone : public sphere{
public:
    cone(double rp = 0, double hp = 0):sphere(rp), height(hp){}

protected:
    double height;

private:
    double get_perimeters() const override {return std::numbers::pi * r * 2;}
    double get_areas() const override {return (std::numbers::pi * r * r + std::numbers::pi * (r * r + height * height));}
};

class A {
public:
    int f() {return func1();}
private:
    virtual int func1() {return 1;}
    int func2() {return 2;}
};

class B : public A {
public:
    int ff() {return 22;}
private:
    int func1() override {return 11;}
    //int bb = func2(); //error func2() is private, and not virtual in class A
};

class C : public B {
    int func1() override {return 111;}
};

int main()
{
    A a;
    B b;
    C c;

    A* p = &a;
    std::cout << p->f() << std::endl; //1

    p = &b; //only class B : public A
    std::cout << p->f() << std::endl; //11

    p = &c; //only class C : public B
    std::cout << p->f() << std::endl; //111

    circle c1(1);
    sphere s1(1);
    cone n1(1,1);

    //Geometric_primitive gobj; //error, cannot create object of abstract class type
    Geometric_primitive* gp = &c1; //only derivation list is public
    gp->print(); //Perimeters: 6.28319, Areas: 3.14159

    gp = &s1; //only derivation list is public
    gp->print(); //Perimeters: 6.28319, Areas: 12.5664

    gp = &n1; //only derivation list is public
    gp->print(); //Perimeters: 6.28319, Areas: 9.42478

}