#include <iostream>
#include <vector>
#include <string>
#include <functional> //for bind function
#include <algorithm>

bool isshoter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

bool check_size(const std::string &s1, std::vector<std::string>::size_type sz)
{
    return s1.size() <= 6;
}

int main()
{
    std::vector<std::string> vec_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    //==== using lambda ====
    //first sort with size(), larger size first
    std::sort(vec_s.begin(), vec_s.end(), [](const std::string &s1, const std::string &s2){return s1.size() > s2.size();});
    //find first element size <= 6
    auto iter = std::find_if(vec_s.begin(), vec_s.end(), [](const std::string &s)->bool{return s.size() <= 6;});
    //count how many element size <= 6
    auto count = vec_s.end() - iter;
    std::cout << "There are " << count << " elements with size equal to or smaller than 6." << std::endl; //10

    //==== using functions ====
    //first sort, since we using is shorter, shorte word comes first
    //but we want longer words comes first
    //using bind
    auto r_isshorter = std::bind(isshoter, std::placeholders::_2, std::placeholders::_1);
    /*
    std::string s1 = "af";
    std::string s2 = "awee";
    bool b1 = r_isshorter(s1, s2); // call isshorter(s2, s1), false
    std::cout << b1 <<std::endl; //0
    */
    std::sort(vec_s.begin(), vec_s.end(), r_isshorter);
    //when call r_isshorter, sort() call r_isshorter(s1, s2), which is call isshorter(s2, s1),
    //predicates became return s2.size() < s1.size(); which means longer words comes first

    //now use find if, unary predicate, takes only 1 parameter, while check_size() takes 2 parameter
  
    auto check_size_bind = std::bind(check_size, std::placeholders::_1, 6);
    //now check_size_bind takes only 1 parameter, which is const string&, corresponding to check_size() parameter
    auto iter_2 = std::find_if(vec_s.begin(), vec_s.end(), check_size_bind);
    std::cout << "There are " << vec_s.end() - iter_2 << " elements with size equal to or smaller than 6." << std::endl; //10

}