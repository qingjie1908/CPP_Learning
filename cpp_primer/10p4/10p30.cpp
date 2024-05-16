#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::istream_iterator<int> is_iter(std::cin);
    std::istream_iterator<int> is_eof;

    std::vector<int> vec_i1;

    //now vec_i1 has int read from std::cin
    //it's like inserter_vec_i1 = is_iter
    //then call vec.push_back()
    //until hit end of life in std::cin
    std::copy(is_iter, is_eof, std::insert_iterator(vec_i1, vec_i1.begin()));

    //now sort vec_i1
    std::sort(vec_i1.begin(), vec_i1.end()); //default predicate using < operator

    //now print vec_is to std::cout
    std::ostream_iterator<int> os_iter(std::cout, " ");

    std::copy(vec_i1.begin(), vec_i1.end(), os_iter);
    //*os_iter = "\n"; //wrong because os_iter bind std::cout with type int, not string
    std::cout << std::endl;

    std::unique_copy(vec_i1.begin(), vec_i1.end(), os_iter);
    std::cout << std::endl;

    return 0;

}