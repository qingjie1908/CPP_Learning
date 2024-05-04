#include <iostream>
#include <vector>
#include <string>

bool find_value(std::__1::vector<int>::iterator begin, std::__1::vector<int>::iterator end, int value)
{
    bool bit = false;
    while (begin != end){
        if(*begin == value){
            bit = true;
            break;
        }
        ++begin;
    }

    return bit;
}


int sum(int a, int b)
{
    return a + b;
}

int main()
{
    std::vector<int> i_vec1 = {1, 32, 4, 543, 2, 4, 56, 4};

    int check_value = 44;

    bool is_find;
    auto begin = i_vec1.begin();
    auto end = i_vec1.end();

    is_find = find_value(begin, end, check_value);

    is_find ? std::cout << "find value " << check_value << std::endl : std::cout << "not find value " << check_value << std::endl;

    return 0;

}