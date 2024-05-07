#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

int main()
{
    int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
    std::vector<int> vec1;
    std::list<int> lst1;

    for (auto item : ia) {
        vec1.push_back(item);
        lst1.push_back(item);
    }

    for(auto iter = lst1.begin(); iter != lst1.end(); /*no expression*/) {
        if(*iter%2){//is odd value, erase
            iter = lst1.erase(iter); //now iter point to next item, no need to ++
        } else {
            ++iter;
        }
    }

    std::cout << "lst1 without odd vale: " << std::endl;
    for(auto item : lst1) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    for(auto iter = vec1.begin(); iter != vec1.end(); /*no expression here*/) {
        if(*iter%2){ //is odd value, keep
            ++iter;
        } else { //is even value, erase
            iter = vec1.erase(iter); //now iter point to next item, no need to ++
        }
    }

    std::cout << "vec1 without even value: " << std::endl;
    for(auto item : vec1) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
    
}