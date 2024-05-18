#include <map>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> family_name = {"A", "B", "C"};
    std::vector<std::string> child_name = {"aa", "cc", "bb", "dd"};

    std::multimap<std::string, std::string> family_map;

    for(auto family_n : family_name){
        for(auto child_n :child_name){
            family_map.insert({family_n, child_n}); //multimap, no need to check unique key
            //they will be added each time
        }
    }

    for (auto item : family_map){
        std::cout << item.first << " : " << item.second << std::endl;
    }
    //output
    /*
    A : aa
    A : cc
    A : bb
    A : dd
    B : aa
    B : cc
    B : bb
    B : dd
    C : aa
    C : cc
    C : bb
    C : dd
    */

    return 0;
}