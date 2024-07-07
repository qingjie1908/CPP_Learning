#include <string>
#include <iostream>

template<typename T, typename... Args>
void foo(const T& t, const Args&... rest)
{
    std::cout << sizeof...(Args) << ", " << sizeof...(rest) << std::endl; 
}



int main(){
    int i = 0; double d = 3.14; std::string s = "how now brwon cow";
    foo(i, s, 42, d);
    //void foo(const int&, const string&, const int&, const double&); sizeof...(Args) is 3, sizeof...(rest) is 3

    foo(i, s, s, d); //3, 3; Args only have 3: string, string and double, rest has 3 parameters

    foo(s, 42, "hi"); //2, 2

    foo(d, s); //1, 1

    foo("hi"); //0, 0

    return 0;
    
}