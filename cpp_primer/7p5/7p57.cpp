#include <iostream>
#include <string>
#include <vector>

using std::vector;

class Account{
public:
    void calculate() {amount += amount * interestRate;}
    static double rate() {return interestRate;}
    static void rate(double);
public:
    // here interestRate is non-const static member, so cannot have in-class initializer, need to be definded out of any function
    static double interestRate;
private:
    std::string owner;
    double amount;
    static double initRate() {return 0.03;}
    // here interstR_const is const static member, so can have in-class initialier
    // the in-class initializer must be constatnt expressions
    // ordinarylly we shoud also define cont static member outside class
    // and constexpr specifier is a must
    // cannot use 'static const double interstR_const = 0.01;'
    static constexpr double interstR_const = 0.01;
    static const int aninteger = 1;
    
};

// once decalared as static member in the class, oustside defination has no 'static' specifier
void Account::rate(double newRate)
{
    interestRate = newRate; // after Account::, the interestRate is in scope and can be accessed from class no matter for private or public class member
}

// defind non-const static member outside class, also need to omit static specifier
double Account::interestRate = 0.03;

// error1: redefination
// error2: cannot not call non-constexpre function
// const double Account::interstR_const = std::cin.get();

class Example{
public:
    // static double rate = 6.5; //error, non-const static member initializer must be out of class
    // static constexpr double rate = 6.5; must have constexpr specifier
    static double rate;
    static constexpr int vecSize = 20;
    static std::vector<double> vec2;
};

double Example::rate = 6.5;
std::vector<double> Example::vec2(Example::vecSize);



int main()
{
    // access interestRate using scope operator
    std::cout << Account::interestRate << std::endl; //0.03
    Account obj1;
    obj1.interestRate = 0.02;
    std::cout << Account::interestRate << std::endl; //0.02

    // static member can be argument, also can be default argument
    // Here is argument since we are using it not define it
    Account::rate(Account::interestRate * 2);
    std::cout << Account::interestRate << std::endl; //0.04

    std::vector<double> vec1(Example::vecSize);
    std::cout << vec1[0] << std::endl; //0
    vec1[0] = 1;
    std::cout << vec1[0] << std::endl; //1
    Example::vec2[0] = 2;
    std::cout << Example::vec2[0] << std::endl; //2

    return 0;

}
