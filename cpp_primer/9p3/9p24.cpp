#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>

int main()
{
    std::vector<int> i_vec1 = {3, 543, 43, 34};
    std::vector<int> i_vec2;

    std::cout << "i_vec1.at(0): " << i_vec1.at(0) << std::endl;
    std::cout << "i_vec1[0]: " << i_vec1[0] << std::endl;
    std::cout << "i_vec1.front(): " << i_vec1.front() << std::endl;
    std::cout << "*i_vec1.begin(): " << *i_vec1.begin() << std::endl;

    std::cout << "i_vec2.at(0): " << i_vec2.at(0) << std::endl;
    std::cout << "i_vec2.[0]: " << i_vec2[0] << std::endl;
    std::cout << "i_vec2.front(): " << i_vec2.front() << std::endl;
    std::cout << "*i_vec2.begin(): " << *i_vec2.begin() << std::endl;
    /*
    i_vec1.at(0): 3
    i_vec1[0]: 3
    i_vec1.front(): 3
    *i_vec1.begin(): 3
    i_vec2.at(0): libc++abi: terminating due to uncaught exception of type std::out_of_range: vector
    /bin/sh: line 1: 42460 Abort trap: 6           "/Users/qingjie/github/CPP_Learning/cpp_primer/9p3/"9p24
    */
    return 0;

}
