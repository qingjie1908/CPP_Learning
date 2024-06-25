template <typename T_iter, typename T_val>
T_iter my_find(const T_iter& iter_start, const T_iter& iter_end, const T_val& val){
    auto curr = iter_start; //make sure T_iter type can be copy construct
    while(curr != iter_end){
        if(*curr == val){ //ensure curr can be dereference, and can *curr can be compare with val
            break;
        }
        ++curr; //ensure curr have prefix ++ operator
    }
    return curr;
}

#include <vector>
#include <list>
#include <string>
#include <iostream>

int main()
{
    std::vector<int> vec_i = {1, 3, 5, 6, 6};

    auto ret = my_find(vec_i.begin(), vec_i.end(), 6);
    if (ret != vec_i.end()){
        std::cout << "find element " << *ret << " in this vec" << std::endl;
    } else {
        std::cout << "not find element in this vec" << std::endl;
    }

    ret = my_find(vec_i.begin(), vec_i.end(), 7);
    if (ret != vec_i.end()){
        std::cout << "find element " << *ret << " in this vec" << std::endl;
    } else {
        std::cout << "not find element " <<  " in this vec" << std::endl;
    }

    std::list<std::string> lst_s = {"aa", "bb", "cc", "dd"};
    auto ret2 = my_find(lst_s.begin(), lst_s.end(), "aa");
    if (ret2 != lst_s.end()){
        std::cout << "find element " << *ret2 << " in this vec" << std::endl;
    } else {
        std::cout << "not find element in this vec" << std::endl;
    }

    ret2 = my_find(lst_s.begin(), lst_s.end(), "a");
        if (ret2 != lst_s.end()){
        std::cout << "find element " << *ret2 << " in this vec" << std::endl;
    } else {
        std::cout << "not find element in this vec" << std::endl;
    }

    return 0;
}
