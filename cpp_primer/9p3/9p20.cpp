#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

int main()
{
    std::list<int> lst1 = {23, 23, 4, 567, 8, 36, 7};

    std::deque<int> dq_even;
    std::deque<int> dq_odd;

    for(auto item : lst1) {
        if (item%2 == 0) {
            dq_even.push_back(item);
        } else {
            dq_odd.push_back(item);
        }
    }

    std::cout << "dq_even are: " << std::endl;
    for(auto item : dq_even) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::cout << "dq_odd are: " << std::endl;
    for(auto item : dq_odd) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    std::cout << "input some strings into vector: " << std::endl;
    std::string word;
    std::vector<std::string> s_vec;
    auto iter_begin = s_vec.begin();
    while (std::cin >> word) {
        iter_begin = s_vec.insert(iter_begin, word); // like push_front
    }
    

    std::cout << "output string vector like push front: " << std::endl;
    for (auto item : s_vec) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}