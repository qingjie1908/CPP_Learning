#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

template<typename T, typename U>
auto m_count(const T& vec, const U& val) -> decltype(vec.size())
//a trailing return lets us declare the return type after the parameter list is seen
{
    auto curr = vec.begin(); //if vec<const char* p>, then *curr is p, which is "aa", **curr is *p, which is 'a'
    decltype(vec.size()) ret = 0;
    while(curr != vec.end()){
        if (*curr == val){
            ++ret;
        }
        ++curr;
    }
    return ret;
}

//orginal template can also handle const char* vec,
//function template specialization must specify each argument type, a specialization is an instantiation
//here if U is const char*, const U&, U base type is *, reference to const U then is reference to const * (which is * const & arg), that pointer point point to const char (then add const char, which is const char * const & arg)
//but m_count(vec5, "aaa") will not choose this specialization, cause const char[4]& is more specialized than const char * const &, so will use first template to instantiation
//if speclization is template<> auto m_count(const std::vector<const char*>& vec, const string & val) -> decltype(vec.size()), then will choose this specialization
//if there is another non-template version match equally good, like third one, then m_count(vec5, "aaa") will use the non-template version
template<>
auto m_count(const std::vector<const char*>& vec, const char * const & val) -> decltype(vec.size())
//a trailing return lets us declare the return type after the parameter list is seen
{
    auto curr = vec.begin();
    decltype(vec.size()) ret = 0;
    while(curr != vec.end()){
        if (*curr == val){
            ++ret;
        }
        ++curr;
    }
    return ret;
}

//non-template version
auto m_count(const std::vector<const char*>& vec, const char * const & val) -> decltype(vec.size())
//a trailing return lets us declare the return type after the parameter list is seen
{
    auto curr = vec.begin();
    decltype(vec.size()) ret = 0;
    while(curr != vec.end()){
        if (*curr == val){
            ++ret;
        }
        ++curr;
    }
    return ret;
}



int main(){
    std::vector<int> vec1 = {1,3,5,5,5,9,9};
    std::vector<double> vec2 = {5,7,7,8,9,10};
    std::vector<std::string> vec3 = {"aa", "bb", "ccd"};
    std::string s1 = "aaa", s2 = "bbb", s3 = "ccc";
    std::vector<std::string> vec4 = {s1, s2, s3};

    const char* p1 = "aaa", * p2 = "aa", * p3 = "ccc";
    std::vector<const char*> vec5 = {p1, p2, p3};

    std::cout << m_count(vec1, 5) << std::endl; //3
    std::cout << m_count(vec2, 7) << std::endl; //2
    std::cout << m_count(vec3, "aa") << std::endl; //1
    std::cout << m_count(vec4, s1) << std::endl; //1
    std::cout << m_count(vec5, "aaa") << std::endl; //1
}