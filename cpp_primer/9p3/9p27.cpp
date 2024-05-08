#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>


void find_n_insert(std::forward_list<std::string> &f_lst, std::string const& str1, std::string const& str2)
{
    //find first occurrence of str1 in f_lst, insert str2 following str1
    auto prev = f_lst.before_begin();
    auto curr = f_lst.begin();

    while(curr != f_lst.end()) {
        if(*curr == str1){ // find first occurence of str1
            //insert str2 after str1
            prev = f_lst.insert_after(curr, str2); // insert str2 after str1, and now return iter point to str2
            ++ curr; ++ curr; //update curr
            break; // since only find one occur, break, 
        } else {
            prev = curr;
            ++curr;
        }
    }

    if (curr == f_lst.end()) {
        //scan all and not find element
        f_lst.insert_after(prev, str2); //note pre is the last element now
    }
}

int main()
{
    std::forward_list<int> f_lst1 = {256, 34, 3, 65, 23, 786, 34, 45};

    //find and remove odd value in f_lst1
    auto prev = f_lst1.before_begin();
    auto curr = f_lst1.begin();

    while(curr != f_lst1.end()){
        if(*curr%2){ //is odd, erase
            curr = f_lst1.erase_after(prev); // erase curr and return next element's iter to curr
            //prev no need to change cause prev next element is still curr
        } else {
            //updaet prev to curr so curr can move on
            prev = curr;
            ++curr; // curr move on
        }
    }

    std::cout << "now f_lst1 without odd value: " << std::endl;
    for (auto item : f_lst1) {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //==== ex9.28 ====

    // char arr[3][5] = {"this", "is", "a"};
    // char (*a)[] = arr;

    // char brr[6] = "this";
    // char *b = brr;

    // char* crr[] = {"this", "is", "a"};
    // crr[0] = "thisis";

    std::forward_list<std::string> f_lst2 = {"this", "is", "a", "happy", "world", "this", "is"};

    find_n_insert(f_lst2, "is", "really"); // add "really" before first "is" in f_lst2

    std::cout << "now f_lst2 is: " << std::endl;
    for(auto item : f_lst2){
        std::cout << item << " ";
    }
    std::cout << std::endl;

}