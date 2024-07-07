#include <string>
#include <iostream>

// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template<typename T>
std::ostream& print(std::ostream& os, const T& t){
    return os << t;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest){
    os << t <<", ";
    return print(os, rest...);
}
//For the last call in the recursion, print(cout, 42), both versions of print are viable. This call passes exactly two arguments
//Hence, the variadic version of print can be instantiated with only two parameters: one for the ostream& parameter and the other for the const T& parameter.
//However, a non- variadic template is more specialized than a variadic template, so the nonvariadic version is chosen for this call 
//A declaration for the nonvariadic version of print must be in scope when the variadic version is defined. Otherwise, the variadic function will recurse indefinitely.

//if put first template after second template func,
// for return print(os, rest…), compiler will flag error: no matching function for call to print

struct ms{
    int a = 10;
};

int main()
{
    int i = 42;
    std::string s = "a";
    ms ms1;
    print(std::cout, i, s, "hello", 42) << std::endl; //42, a, hello, 42
    //instantiate print<int, string, char [6], int>(ostream&, const int&, const std::string&, const (&) [6], const int&)


    //print(std::cout, i, ms1); error, ms1 has no << operator
}