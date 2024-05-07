#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

int main()
{
    std::vector<int> iv = {4, 4, 5, 7, 4, 10, 11};

    std::vector<int>::iterator iter = iv.begin(), mid = iv.begin() + iv.size()/2;

    int some_val = 4;

    while (iter != mid) {
        if (*iter == some_val) {
            iter = iv.insert(iter, 2 * some_val); // this will destroyred previous iter and mid, need to be updated
            iter = iter + 2; // move to originall pos, then move to next element need to be checked
            mid = iv.begin() + iv.size()/2;
        } else {
            // if not find equal value then no need to update mid and iter
            ++iter; 
        }      
    }

    std::cout << "updated iv are: " << std::endl;
    for (auto item: iv) {
        std::cout << item << " ";
    } // 8 4 8 4 5 7 4 10 11

    std::cout << std::endl;
    return 0;
}