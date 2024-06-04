#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/StrVec.h"
#include <iostream>
int main()
{
    StrVec obj1;
    obj1.push_back("a");

    StrVec obj2(obj1);

    obj2.push_back("b");

    obj1 = obj2;
    //obj1 and obj2 pointed dynamic string memory address changed
    //but &obj1 and &obj2 are unchanged

    std::cout << "check" << std::endl;

    StrVec obj3({"aa", "bb", "cc"}); //size = 3, capacity = 3;

    obj3.reserve(2); //nothing should happen; size = 3; capacity = 3

    obj3.reserve(5); //size = 3; capacity = 5;

    obj3.resize(10); //size = 10; capacity = 10; obj3 last 7 element are constructed empty string

    obj3.resize(10, "xx"); //size did not change, so XX will not write into element, last 7 element are still ""

    obj3.resize(12, "xx"); //now last element will be filled by "xx"; which is obj.begin()+10/11

    obj3.reserve(2); //not change obj3

    //move constructor
    StrVec obj4(std::move(obj1)); //now obj1 three member pointers point to nothing (nullptr), obj4.size() = 2, obj1.size() = 0

    //move assignment operator
    obj4 = std::move(obj3); // now obj3 pointers point to nullptr, obj4.size() = 12, obj3.size() = 0;

}