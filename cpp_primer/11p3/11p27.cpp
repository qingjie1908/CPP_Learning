#include <map>
#include <vector>
#include <iostream>
#include <string>

int main()
{
    std::multimap<std::string, std::vector<int>> map1 = {   {"a", {1, 2, 3}},
                                                            {"b", {2, 3, 4}},
                                                            {"c", {3, 4, 5}},
                                                            {"a", {4, 5, 6}}};
    //after map1 initialized, they will be ordered with strcik weak order for key, so "a" will be adjacent
    auto iter = map1.find("a"); //point to first a

    for(auto item : map1){
        std::cout << item.first << " has int : ";
        for(auto number : item.second){
            std::cout << number << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "The second key \"a\" has ints: ";
    for(auto number : (++iter)->second){
        std::cout << number << " ";
    }
    std::cout << std::endl;
    //output:
    // a has int : 1 2 3 
    // a has int : 4 5 6 
    // b has int : 2 3 4 
    // c has int : 3 4 5 
    // The second key "a" has ints: 4 5 6 

}