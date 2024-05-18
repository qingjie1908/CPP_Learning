#include <map>
#include <iostream>

int main()
{
    std::map<std::string, int> map1= {{"afs", 1}, {"ew", 3}, {"dsf", 7}, {"hjasd", 0}, {"tr", 9}};
    auto it = map1.begin();

    for(int i = 0; i < 5; ++i){
        (*it).second = 3;
        ++it;
    }

    for (auto item : map1){
        std::cout << item.first << item.second << std::endl;
    }
}