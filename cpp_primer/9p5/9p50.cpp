#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> vec_s = {"123", "6a4", "029", "0xa", "0.7"};

    //The first non-whitespace character in the string we convert to numeric value must be a character that can appear in a number:
    //a64 is error if the base is decimal, also .53 is error in stoi

    for (std::string item : {"123", "6a4", "029", "0xa", "0.7"}){
        std::cout << stoi(item) << " "; //123 6 29 0 0 
    }
    std::cout << std::endl;

    for (std::string item : {"123", "6a4", "029", "0xa", "0.7"}){
        std::cout << stoi(item, 0, 16) << " "; //291 1700 41 10 0
    }
    std::cout << std::endl;

    for (std::string item : {"123", "6a4", "029", "0xa", "0.7"}){
        std::cout << stoi(item, 0, 8) << " "; //83 6 2 0 0
    }
    std::cout << std::endl;

    for (std::string item : {"123", "6a4", "029", "0xa", "0.7"}){
        std::cout << stod(item) << " "; //123 6 29 10 0.7
    }
    std::cout << std::endl;

    double sum = 0;
    for(auto item : vec_s){
        sum += stoi(item); //123+6+29+0+0 = 158
    }
    std::cout << "sum of vec_s element convert to int are: " << sum << std::endl;

    sum = 0;
    for(auto item : vec_s){
        sum += stod(item); //123 + 6 + 29 + 10 + 0.7 = 168.7
    }
    std::cout << "sum of vec_s element convert to double are: " << sum << std::endl;

    return 0;
}