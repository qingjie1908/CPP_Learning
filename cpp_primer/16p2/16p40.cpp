template<typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
    return *beg; //dereference return lvalue, so return reference, but we want to return a copy of an element, no beg itself
    //so return decltype(*beg + 0), which will return not reference, but a rvalue;
}






#include <vector>
#include <string>

int main(){
    std::vector<int> vec1 = {2,3,5,7,8};
    std::vector<std::string> vec2 = {"aa", "bb", "cc"};

    auto ret1 = fcn3(vec1.begin(), vec1.end());
    //auto ret2 = fcn3(vec2.begin(), vec2.end()); //no string + 0, error


    }