#include <tuple>
#include <string>
#include <vector>
#include <iostream>

int main(){
    std::tuple<int, int, int> t1(10, 20, 30);
    std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> t2;

    std::cout << std::get<1>(t1) << std::endl;//20
    std::cout << std::tuple_size<decltype(t1)>::value << std::endl;//3
    std::tuple_element<1, decltype(t2)>::type vec1 = std::get<1>(t2);
    vec1.push_back("hellp");

    return 0;
}