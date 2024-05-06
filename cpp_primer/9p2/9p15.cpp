#include <iostream>
#include <vector>
#include <list>

int main()
{
    std::vector<int> i_vec1 = {1, 3, 245, 4};
    std::vector<int> i_vec2 = {1, 3, 245, 3, 43};
    
    (i_vec1 == i_vec2) ? (std::cout << "i_vec1 = i_vec2" << std::endl) : (std::cout << "i_vec1 != i_vec2" << std::endl);

    std::list<int> lst1 = {1, 3, 245, 3, 43};

    //auto smaller_size = i_vec1.size() <= lst1.size() ? i_vec1.size() : lst1.size();

    auto begin_vec =  i_vec1.begin();
    auto end_vec = i_vec1.end();

    auto begin_lst = lst1.begin();
    auto end_lst = lst1.end();

    while ((begin_vec != end_vec) && (begin_lst != end_lst)) { // only compare correponding element and stop at samller size point
        if (*begin_vec != *begin_lst) {
            if (*begin_vec < *begin_lst) {
                std::cout << "i_vec1 < lst1" << std::endl;
            } else {
                std::cout << "i_vec1 > lst1" << std::endl;
            }
            break;
        }
        ++begin_vec;
        ++begin_lst;
    }

    //check if compare all elements between i_vec1 and lst1
    if(begin_vec == end_vec || begin_lst == end_lst) { // compare all corresponding element and they are equal for smaller size
        if (i_vec1.size() != lst1.size()) {
            if (i_vec1.size() < lst1.size()) {
                std::cout << "i_vec1 < lst1" << std::endl;
            } else {
                std::cout << "i_vec1 > lst1" << std::endl;
            }
        } else {
            std::cout << "i_vec1 = lst1" << std::endl;
        }
    }

    return 0;

}