#include <iostream>
#include <string>

int main()
{
    std::string s1("ab2c3d7R4E6");

    //find each numeric char in string
    std::string numbers("0123456789");

    decltype(s1.size()) pos = 0;
    //The library defines npos as a const string::size_type initialized with the value -1. 
    //Because npos is an unsigned type, this initializer means npos is equal to the largest possible size any string could have
    while ((pos = s1.find_first_of(numbers, pos)) != std::string::npos){
        std::cout << "find number at s1[" << pos << "]: "<< s1[pos] << std::endl;
        ++pos;
    }

    //find each alphabetic char in s1

    pos = 0;

    while ((pos = s1.find_first_not_of(numbers, pos)) != std::string::npos){
        std::cout << "find non-number at s1[" << pos << "]: "<< s1[pos] << std::endl;
        ++pos;
    }

    //==== ex 9.48 ====

    std::string name("r2d2");
    //numbers = "ewafrr2d22";
    pos = numbers.find(name);
    if (pos != std::string::npos){
        std::cout << "find first occurrence of \"r2d2\" in numbers starting at pos: " << pos << std::endl;
    }

    if (pos == std::string::npos){
        std::cout << "not find occurrence of \"r2d2\" in numbers" << std::endl;
    }

    return 0;

}