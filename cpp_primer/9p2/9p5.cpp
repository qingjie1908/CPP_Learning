#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>


std::vector<int>::iterator find_value(std::__1::vector<int>::iterator begin, std::__1::vector<int>::iterator end, int value)
{
    decltype(begin) find_iter;

    while (begin != end){
        if(*begin == value){
            find_iter = begin;
            break;
        }
        ++begin;
    }

    find_iter = begin; // if not find, at last begin = end; if find value then find_iter will = begin

    return find_iter;
}


int sum(int a, int b)
{
    return a + b;
}

int main()
{
    std::vector<int> i_vec1 = {3, 32, 4, 543, 2, 4, 56, 4};

    int check_value = 44;

    decltype(i_vec1.begin()) is_find;
    auto begin = i_vec1.begin();
    auto end = i_vec1.end();

    is_find = find_value(begin, end, check_value);

    if (is_find == end) {
        std::cerr << "not find element" << std::endl;
    } else {
        std::cout << "find element " << *is_find << std::endl;
    }

    std::list<int> lst1 = {2, 5, 7};
    std::list<int>::iterator iter1 = lst1.begin(), iter2 = lst1.end();
    int i = 0;
    while (iter1 != iter2) {
        std::cout << "lst1[" << i << "] = " << *iter1 << std::endl;
        ++i;
        ++iter1;
    }

    return 0;

}