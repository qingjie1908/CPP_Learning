#include <vector>
#include <iostream>
#include <string>
#include <list>

int main()
{
    //==== ex 10.1 ====
    std::vector<int> vec_i = {3, 54, 7, 875, 43, 3, 3};
    auto result_1 = count(vec_i.begin(), vec_i.end(), 3);
    auto result_2 = find(vec_i.begin(), vec_i.end(), 3);

    std::cout << "There are " << result_1 << " occurrence of interger 3 in this vector." << std::endl;
    std::cout << "first interger 3 is *result_2: " << *result_2 << std::endl;

    //==== ex 10.2 ====
    std::list<std::string> list_str = {"a", "ab", "ba", "a", "aa", ""};
    std::string check_str = "a";
    auto result_3 = count(list_str.begin(), list_str.end(), check_str);
    auto result_4 = find(list_str.begin(), list_str.end(), check_str);

    std::cout << "There are " << result_3 << " occurrence of string \"a\" in this list." << std::endl;
    std::cout << "first string a is *result_4: " << *result_4 << ", its next element is: " << *(++result_4) << std::endl;

    return 0;
}