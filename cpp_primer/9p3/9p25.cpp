#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

int main()
{
    std::vector<int> i_vec1 = {232, 43, 3, 546, 2, 56, 76, 340};
    auto elem1 = i_vec1.begin() + 2; //3
    auto elem2 = i_vec1.begin() + 5; //56
    auto elem3 = i_vec1.begin() + 6; //76

    i_vec1.erase(elem1, elem2); // not include elem2

    //Iterators, references, and pointers to elements after the erasure point (which is elem1) in a vector or string are invalidated
    //so elem1 are still validated
    //elem2 and elem3 not validated although *elem2 and elem3 will have vaule
    //but erase(elem2) or erase(elem3) will cause error
    std::cout << *elem1 << " " << *elem2 << std::endl; //now both elem1 and elem2 point to 56
    std::cout << *elem3 << std::endl; //76
    for(auto item : i_vec1) { //232 43 56 76 340
        std::cout << item << " ";
    }
    std::cout << std::endl;

    i_vec1.erase(elem1,elem2); //elem2 is not validated now, it will remove all elements after and include 56
    std::cout << *elem1 << " " << *elem2 << std::endl; //56 56
    std::cout << *elem3 << std::endl; //76
    for(auto item : i_vec1) { //232 43
        std::cout << item << " ";
    }
    std::cout << std::endl;

    auto elem4 = i_vec1.end();
    auto elem5 = i_vec1.end();
    i_vec1.erase(elem4, elem5);
    std::cout << *elem1 << " " << *elem2 << std::endl; //56 56
    for(auto item : i_vec1) { //232 43
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}