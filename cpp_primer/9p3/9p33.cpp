#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

int main()
{
    // silly loop to insert a 2 * odd-valued element after this odd element
    std::vector<int> vi = {0,1,2,3,4,5,6,7,8,9}; 
    auto iter = vi.begin();// call begin,not cbegin because we’rechanging vi
    while (iter != vi.end()) { 
        if (*iter % 2) {
            auto prev = iter;
            ++iter;
            iter = vi.insert(iter, *prev * 2); // insert after current odd value
            //if we did not assign the insert() result to iter
            //then iter will be invalidated
            // ++iter and *iter will be disaster
            ++iter; // advance past this element and the one inserted before it 
        } else
            ++iter;    
    }

    for(auto item : vi){
        std::cout << item << " ";
    }
    std::cout << std::endl; //0 1 2 2 3 6 4 5 10 6 7 14 8 9 18

    auto begin = vi.begin();
    while(begin != vi.end())
    {
        if(*begin % 2){
            begin = vi.insert(begin, *begin);
            ++begin;
            ++begin;
        } else {
            ++begin;
        }
    }

    for (auto item : vi){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}