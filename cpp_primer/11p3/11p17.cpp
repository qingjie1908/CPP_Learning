#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

int main()
{
    std::multiset<std::string> c = {"aa", "aa", "aaa", "abc", "bc"};

    std::vector<std::string> v = {"efa", "aa", "abc"};

    copy(v.begin(), v.end(), inserter(c, c.end()));
    for(auto item : c){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //illegal, c has no push_back
    // copy(v.begin(), v.end(), back_inserter(c));
    // for(auto item : c){
    //     std::cout << item << " ";
    // }
    // std::cout << std::endl;

    copy(c.begin(), c.end(), inserter(v, v.end()));
    copy(c.begin(), c.end(), back_inserter(v));
}