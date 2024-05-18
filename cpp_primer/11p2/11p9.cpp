#include <map>
#include <list>
#include <iostream>

int main()
{
    std::list<int> line_numbers = {1, 23, 54, 2, 3, 3};
    std::map<std::string , int> word_on_line;

    auto iter = line_numbers.begin();
    for(auto item :  {"a", "b", "c", "d", "e", "f"}){
        word_on_line[item] = *iter;
        ++iter;
    }

    for(auto item : word_on_line){
        std::cout << item.first << " : " << item.second << std::endl; 
    }


}