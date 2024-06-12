#include <functional> //use library function Objects
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    //count the number of values that are greater than 1024
    std::greater<int> obj1; //obj1 take two parameter
    auto f = std::bind(obj1, std::placeholders::_1, 1024);
    
    std::vector<int> vec1 = {1025, 1023, 1024, 1025, 1023};
    auto count = std::count_if(vec1.begin(), vec1.end(), f);
    std::cout << count << " elements has value larger than 1024." << std::endl; //2
    //same effect
    count = std::count_if(vec1.begin(), vec1.end(), std::bind(std::greater<int>(), std::placeholders::_1, 1024));
    std::cout << count << " elements has value larger than 1024." << std::endl; //2

    //find first string that is not equal to "pooh"
    std::vector<std::string> vec2 = {"pooh", "pooj", "pooh", "poox"};
    auto first = std::find_if(vec2.begin(), vec2.end(), std::bind(std::not_equal_to<std::string>(),  std::placeholders::_1, "pooh"));
    std::cout << *first << std::endl; //pooj

    //multiply all values by 2
    std::multiplies<int> obj2;
    for(auto& item : vec1){
        item = obj2(item, 2);
    }
    std::for_each(vec1.begin(), vec1.end(), [](const int& i){std::cout << i << " ";});
    
    return 0;

}