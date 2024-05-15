#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <forward_list>
#include <deque>

int main()
{
    std::vector<int> vec_i = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::list<int> lst1, lst2, lst3;

    std::copy(vec_i.begin(), vec_i.end(), std::inserter(lst1, lst1.begin()));
    std::copy(vec_i.begin(), vec_i.end(), std::back_inserter(lst2));
    std::copy(vec_i.begin(), vec_i.end(), std::front_inserter(lst3));

    for(auto lst : {lst1, lst2, lst3}){
        for(auto item : lst){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    //output
    /*
    1 2 3 4 5 6 7 8 9 
    1 2 3 4 5 6 7 8 9 
    9 8 7 6 5 4 3 2 1 
    */

    std::forward_list<int> f_lst1, f_lst2, f_lst3;
    //std::copy(vec_i.begin(), vec_i.end(), std::inserter(f_lst1, f_lst1.begin())); not available
    //std::copy(vec_i.begin(), vec_i.end(), std::back_inserter(f_lst2)); // not available
    std::copy(vec_i.begin(), vec_i.end(), std::front_inserter(f_lst3));

    for(auto lst : {f_lst1, f_lst2, f_lst3}){
        for(auto item : lst){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    //output
    /*
     
     
    9 8 7 6 5 4 3 2 1 
    */

    std::deque<int> dq1, dq2, dq3;
    std::copy(vec_i.begin(), vec_i.end(), std::inserter(dq1, dq1.begin()));
    std::copy(vec_i.begin(), vec_i.end(), std::back_inserter(dq2));
    std::copy(vec_i.begin(), vec_i.end(), std::front_inserter(dq3));
    for(auto dq : {dq1, dq2, dq3}){
        for(auto item : dq){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    //output
    /*
    1 2 3 4 5 6 7 8 9 
    1 2 3 4 5 6 7 8 9 
    9 8 7 6 5 4 3 2 1
    */

}