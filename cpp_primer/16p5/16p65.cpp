#include <vector>
#include <string>
#include <iostream>
#include <sstream>

template<typename T>
std::string debug_rep(const T& t){
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

//non-template version, choose these two over the template specialization
// std::string debug_rep(char* p){
//     return debug_rep(std::string(p));
// }
// std::string debug_rep(const char* p){
//     return debug_rep(std::string(p));
// }

template<> //specilization, a instantiation, T is const char*
std::string debug_rep(const char * const & p){
    return debug_rep(std::string(p));
}

template<> //specilization, a instantiation T is char*
//T base type is *, const T& then is * const&, point to char, then total is char * const&
std::string debug_rep(char * const & p){
    return debug_rep(std::string(p));
}

template<> //specilization, a instantiation T is char[5]
//when call debug_rep("acx"); will not use this, cause origina template can instantiate T as char[4], which is better match
std::string debug_rep(const char (&p) [5] ){
    return debug_rep(std::string(p));
}

template<> //specilization, a instantiation T is char[4]
//when call debug_rep("acx"); will use this, cause origina template is more general, this one is more specific
std::string debug_rep(const char (&p) [4] ){
    return debug_rep(std::string(p));
}


template<typename T>
std::ostream& print(std::ostream& os, const T& t){
    return os << t;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args&... rest){
    os << t << ", ";
    return print(os, rest...);
}

template<typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest){
    // print(os,debug_rep(a1),debug_rep(a2),...,debug_rep(an)
    return print(os, debug_rep(rest)...); //after call 5x times debug_rep, go to second print template, recurrsive, finally go to first print tempalte, then return
}
//if print(os, debug_rep(rest...));
//passes the pack todebug_rep;print(os,debug_rep(a1,a2,...,an))

int main()
{
    int a = 1;
    double b = 2;
    std::string c = "hello.";
    errorMsg(std::cerr, a, b, c, 42, "abc") << std::endl; //1, 2, hello., 42, abc
    debug_rep("acx");// will not use specilization template<> std::string debug_rep(const char * const & p), cause template template<char [4]> std::string debug_rep(const char (&t) [4]), this instantiation is better match, no pointer conversion
}