#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

int main()
{
    std::vector<std::string> child_name = {"aa", "bb", "cc", "dd"};
    std::vector<std::string> new_family = {"A", "B", "C"};

    //each family has all child, means multiple element can have same key in new_family
    //so use multimap
    std::multimap<std::string, std::string> family_map ; 
    
    for(auto family_key : new_family){
        for(auto child_value : child_name){
            family_map.insert({family_key, child_value});
        }
    }
    
    std::cout << "family_map has " << family_map.size() << " elements." << std::endl;

    for(auto item : family_map){
        std::cout << "Family " << item.first << " has children: " << item.second << std::endl;
    }
    /*
    family_map has 12 elements.
    Family A has children: aa
    Family A has children: bb
    Family A has children: cc
    Family A has children: dd
    Family B has children: aa
    Family B has children: bb
    Family B has children: cc
    Family B has children: dd
    Family C has children: aa
    Family C has children: bb
    Family C has children: cc
    Family C has children: dd
    */

    // ==== ex 11.8 ====
    std::vector<std::string> exclude_vec = {"asd", "daf"};
    std::set<std::string> exclude_set = {"asd", "daf"};

    auto it1 = std::find(exclude_vec.begin(), exclude_vec.end(), "dasf");
    auto it2 = exclude_set.find("dasf");

    if(it1 == exclude_vec.end()){ //true
        std::cout << "dasf not find in vec" << std::endl; 
    }

    if(it2 == exclude_set.end()){ //true
        std::cout << "dasf not find in set" << std::endl; 
    }

    return 0;

}