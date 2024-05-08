#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

int main()
{
    // silly loop to remove even-valued elements and insert a duplicate of odd-valued elements 
    std::vector<int> vi = {0,1,2,3,4,5,6,7,8,9}; 
    auto iter = vi.begin();// call begin,not cbegin because we’rechanging vi
    // while (iter != vi.end()) { 
    //     if (*iter % 2) {
    //         iter = vi.insert(iter, *iter * 2); // duplicate the current element
    //         iter += 2; // advance past this element and the one inserted before it 
    //     } else
    //         iter = vi.erase(iter); // remove even elements
    //         // don’t advance the iterator; iter denotes the element after the one we erased
    // }

    // same effect as previous
    while (iter != vi.end()) { 
        if (*iter % 2) {
            iter = vi.insert(iter, (*iter++)*2); // duplicate the current element
            //*iter++ is *(iter++); iter++ will return copy of orginal iter then increment
            //so *(iter++) will still dereference current iter; after that iter increment
            //but the insert() func return value assigned to iter
            //so iter increment will be override by the assigned iter at last
            /*
            int i = 1;
            i = i++; 
            //final i is still 1 since increment overrride by the =
            */
            iter += 2; // advance past this element and the one inserted before it 
        } else
            iter = vi.erase(iter); // remove even elements
            // don’t advance the iterator; iter denotes the element after the one we erased
    }

    std::cout << "vector now are: " << std::endl;
    for (auto item : vi) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::list<int> li = {0,1,2,3,4,5,6,7,8,9};
    auto iter_li = li.begin();
    while(iter_li != li.end()){
        if (*iter_li % 2){
            iter_li = li.insert(iter_li, *iter_li * 2);
            iter_li ++;
            iter_li ++; //iter += n not allowed for list, only ok for vector and string
        } else {
            iter_li = li.erase(iter_li);
        }
    }

    std::cout << "list now are: " << std::endl;
    for (auto item : li) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::forward_list<int> fli = {0,1,2,3,4,5,6,7,8,9};
    auto prev = fli.before_begin();
    auto curr = fli.begin();
    while(curr != fli.end()) {
        if(*curr % 2){
            curr = fli.insert_after(prev, *curr * 2);
            ++ curr; 
            prev = curr; // update prev
            ++ curr; // update curr
        } else {
            curr = fli.erase_after(prev); // return element after earased
        }
    }
    std::cout << "forward_list now are: " << std::endl;
    for (auto item : fli) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    std::vector<int> vi2 = {0,1,2,3,4,5,6,7,8,9};
    auto iter2 = vi2.begin();
  
    int i = 1;
    int i = i++;
    
    std::cout << i << std::endl; //1, i++ will be override by the final =

    return 0;
}