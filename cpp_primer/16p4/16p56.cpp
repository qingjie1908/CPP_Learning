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
}