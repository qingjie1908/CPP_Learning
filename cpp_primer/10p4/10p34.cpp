#include <iostream>
#include <vector>
#include <string>
#include <list>

int main()
{
    std::vector<std::string> vec_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    //==== ex 10.34 ====
    auto r_iter = vec_s.rbegin();

    while(r_iter != vec_s.rend()){
        std::cout << *r_iter << " ";
        ++r_iter;
    }
    std::cout << std::endl;

    //==== ex 10.35 ====
    auto iter = vec_s.end();
    while(iter != vec_s.begin()){
        --iter;
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    //==== ex 10.36 ====
    std::list<int> lst1 = {1, 4, 0, 111, 34, 53, 0, 0, 5, 5};
    auto r_iter_2 = find(lst1.rbegin(), lst1.rend(), 0);
    int pos = 0;
    while(r_iter_2 != lst1.rbegin()){
        --r_iter_2;
        pos += 1;
    }
    std::cout << "last int 0 is the " << pos + 1 << " element front the back" << std::endl; // 3

    //==== ex 10.37 ====
    std::vector<int> vec_i = {1, 4, 0, 111, 34, 53, 0, 0, 5, 5};
    std::list<int> lst2;

    //copy vec_i[3] to vec_i[7] reverse in lst2;
    auto it = std::inserter(lst2, lst2.begin());
    std::copy(vec_i.rbegin()+3, vec_i.rbegin()+8, it);

    for(auto item : lst2){
        std::cout << item << " ";
    }
    std::cout << std::endl;


    return 0;
}