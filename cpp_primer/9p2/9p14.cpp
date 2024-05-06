#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <fstream>

int main()
{
    std::list<char*> lst1;
    std::vector<std::string> s_vec1;

    lst1 = {"this", "is", "qingjie"};
    s_vec1 = {"that", "were", "apple", "trees"};

    std::list<std::string> lst2 = {"hello", "there"};

    auto begin_lst1 = lst1.begin();
    auto end_lst1 = lst1.end();
    
    s_vec1.assign(begin_lst1, end_lst1); // not inlcude end_lst1 which point to one past last element in lst1
    
    std::cout << "Print item on s_vec1 after assgin: " << std::endl;
    for(auto item : s_vec1) {
        std::cout << item << " ";
    }

    std::cout << std::endl;

    std::cout << "print first and last element in lst1: " << std::endl;
    std::cout << *begin_lst1 << " ";
    std::cout << *(--end_lst1) << std::endl;

    return 0;
}