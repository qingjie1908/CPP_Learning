#include <string>
#include <vector>
#include <iostream>

bool predicate_check_string(std::string& str)
{
    return str.size() >= 5;
}

int main()
{
    std::vector<std::string> vec_s = {"dsa", "sa", "aaefw", "wqrget", "dfsa", "bv"};

    auto iter_part = std::partition(vec_s.begin(), vec_s.end(), predicate_check_string);
    //partition that takes a pred- icate and partitions the container 
    //so that values for which the predicate is true appear in the first part 
    //and those for which the predicate is false appear in the second part

    //returns an iterator just past the last element for which the predicate returned true.

    //print the first part of partitioned vec_s

    auto iter = vec_s.begin();
    
    while(iter != vec_s.end() && iter != iter_part){ //iter_part point to first string element which size is less than 5
        std::cout << *iter << " ";
        ++iter;
    }
    //wqrget aaefw

    return 0;
}