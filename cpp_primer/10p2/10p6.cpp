#include <vector>
#include <iostream>
#include <list>
#include <iterator> // for back_inserter

int main()
{
    //==== ex 10.6 ====
    std::vector<int> vec_i = {3, 4, 65, 875, 92, 1};

    std::fill_n(vec_i.begin(), vec_i.size(), 0);

    for(auto item : vec_i){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //==== ex 10.7 ====
    std::vector<int> vec; std::list<int> lst; int i; 
    for(auto i = 1; i < 5; ++i)
        lst.push_back(i);

    auto back_it = back_inserter(vec); //back_inserter takes a reference to a container and returns an insert iterator bound to that container
    copy(lst.cbegin(), lst.cend(), back_it); //When we assign through that iterator, the assignment calls push_back to add an element with the given value to the container

    for(auto item : vec){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //========
    std::vector<int> vec2;
    vec2.reserve(10); //reserve at leaset 10 capacity memory for vec2
    //but vec2.size() is still 0
    auto back_it2 = back_inserter(vec2);
    std::fill_n(back_it2, 10, 0);
    for(auto item : vec2){
        std::cout << item << " ";
    }
    std::cout << std::endl;

}