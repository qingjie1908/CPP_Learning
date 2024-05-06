#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>


int main()
{
    std::deque<std::string> dq1;
    std::list<std::string> lst1;
    std::string word;
    std::cout << "input some strings" << std::endl;

    while(std::cin >> word) {
        dq1.push_back(word);
        lst1.push_back(word);
    }

    auto iter = dq1.begin();

    std::cout << "deque are: " << std::endl;
    while(iter != dq1.end()) {
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;

    std::cout << "========" << std::endl;

    auto iter_lst = lst1.begin();

    std::cout << "list are: " << std::endl;
    while(iter_lst != lst1.end()) {
        std::cout << *iter_lst << " ";
        ++iter_lst;
    }
    std::cout << std::endl;
    
    return 0;

}