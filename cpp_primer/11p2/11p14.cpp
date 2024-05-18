#include <iostream>
#include <map>
#include <vector>
#include <string>

int main()
{
    std::vector<std::string> child_name = {"b", "a", "c", "d"};
    std::vector<std::string> birthday = {"213", "825", "723", "919"};

    std::vector<std::string> family_name = {"A", "B", "C"};

    std::vector<std::pair<std::string, std::string>> child_birthday;
    for(decltype(child_name.size()) i = 0; i < child_name.size(); ++i ){
        child_birthday.push_back(std::make_pair(child_name[i], birthday[i]));
    }

    std::vector<decltype(child_birthday)> vec(family_name.size(), child_birthday);

    std::multimap<std::string, std::vector<std::pair<std::string, std::string>>> family_map;

    for(size_t i = 0; i < family_name.size(); ++i){
        family_map.insert({family_name[i], vec[i]});
    }

    for (auto item : family_map){
        std::cout << "Family " << item.first << " has: " << std::endl;
        for (auto child : item.second){
            std::cout << "child name: " << child.first << ", birthday: " << child.second << std::endl;
        }
    }

    //output
    /*
    Family A has: 
    child name: b, birthday: 213
    child name: a, birthday: 825
    child name: c, birthday: 723
    child name: d, birthday: 919
    Family B has: 
    child name: b, birthday: 213
    child name: a, birthday: 825
    child name: c, birthday: 723
    child name: d, birthday: 919
    Family C has: 
    child name: b, birthday: 213
    child name: a, birthday: 825
    child name: c, birthday: 723
    child name: d, birthday: 919
    */
}