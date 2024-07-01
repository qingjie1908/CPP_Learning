#include "/Users/qingjie/github/CPP_Learning/cpp_primer/16p1/MyVec.h"
#include <string>
#include <iostream>

int main(){
    myVec<std::string> strvec1 = {"aa", "bb", "cc", "dd"};
    myVec<std::string> strvec2;
    myVec<std::string> strvec3(strvec1);
    strvec2 = strvec1;
    strvec2 = std::move(strvec3);
    myVec<std::string> strvec4 = std::move(strvec1);

    std::cout << strvec2[2] << std::endl; //cc
    strvec2.push_back("ee"); //size() change from 4 to 5, capacity change from 4 to 8
    auto curr = strvec2.begin();
    while(curr != strvec2.end()){
        std::cout << *(curr++) << std::endl; //aa bb cc dd ee
    }

    strvec2.reserve(7); //size() 5, capacity() 8
    strvec2.resize(8); //size() 8, capacity() 8, aa bb cc dd ee "" "" "" (append three empty string)
    strvec2.resize(4); //size() 4, capacity() 4

    std::cout << (strvec2 < strvec4) << std::endl; //0
    std::cout << (strvec4 < strvec2) << std::endl; //0

    myVec<std::string> strvec5(strvec2);
    std::cout << (strvec2 == strvec5) << std::endl; //1
    strvec5[3] = "df";
    std::cout << (strvec2 < strvec5) << std::endl; //1

    strvec2.resize(6, "xy"); //size 6, capacity 6, aa, bb, cc, dd, xy, xy

    //intvec
    myVec<int> intvec1;
    myVec<int> intvec2 = {1, 3, 4, 5};
    myVec<int> intvec3 = intvec2;
    intvec1 = intvec2;
    intvec1 = std::move(intvec2);
    myVec<int> intvec4 = std::move(intvec3);

    std::cout << intvec1[2] << std::endl; //4, size 4, cap 4,
    intvec1.push_back(123); //size 5, cap 8,
    auto curr2 = intvec1.begin();
    while(curr2 != intvec1.end()){
        std::cout << *(curr2++) << std::endl; //1 3 4 5 123
    }

    intvec1.reserve(6); //size 5, cap 8
    intvec1.resize(12); //size 12, cap 12, intvec1[5] to [11] is 0
    intvec1.resize(4); //size 4, cap 4, {1,3,4,5}

    std::cout << (intvec1 < intvec4) << std::endl; //0
    std::cout << (intvec4 < intvec1) << std::endl; //0
    std::cout << (intvec1 == intvec4) << std::endl; //1

    intvec4[2] = 99;
    std::cout << (intvec1 < intvec4) << std::endl; //1

    intvec1.resize(7, 321); //size 7, cap 7, {1,3,4,5,321,321,321}

    return 0;
}