#include <string>
#include <iostream>
#include <sstream>

//first
template<typename T> std::string debug_rep(const T& t){
    std::ostringstream ret;
    ret << t; //use T's << operator
    return ret.str(); //return a copy of string to which ret is bound
}

//second
// this function can’t be used to print character pointers
//because the IO library defines a version of the << for char* values
//That version of << assumes the pointer denotes a null- terminated character array,
//and prints the contents of the array, not its address.
template<typename T> std::string debug_rep(T *p){
    std::ostringstream ret;
    ret << "pointer: " << p;
    if(p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

//third
//non-template
std::string debug_rep(const std::string& s){
    return '"' + s + '"';
}

//fourth
std::string debug_rep(char* p){
    return debug_rep(std::string(p));
}

//fith
std::string debug_rep(const char* p){
    return debug_rep(std::string(p));
}

int main(){
    std::string s("hi");
    std::cout << debug_rep(s) << std::endl;
    //There is no way to instantiate a function template that expects a pointer type from a nonpointer argument
    //call first template version
    //if the non-template version is viable, call non-template version

    std::cout << debug_rep(&s) << std::endl;
    //second version no const conversion, better match

    const std::string *sp = &s;
    std::cout << debug_rep(sp) << std::endl;
    //template debug_rep(const T&) can be called on essentially any type, including pointer types.
    //more general than debug_rep(T*)
    //when several overloaed templates equal good match, most specialized version is preferred. so choose the seconde one

    std::cout << debug_rep("hi world!") << std::endl;
    //first template , T is <char [10]>, exact match, but more general than second template
    //seconde template, T is <const char>, requiere permissible conversion from array to pointer, exact match, best match
    //non-template, require user-defined conversion, const char* to const string

    //if we have fifth
    //then it will call fith, then call return debug_rep(std::string(p));
    //if we do not third std::string debug_rep(const std::string& s) before fith
    //then return will call first template version
    //if defined thrid, then return call will call third
}