#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

class test_size{
public:
    test_size(size_t n):bound(n){}
    bool operator()(const std::string& s) const{ //should not change bound once initialized
        return s.size() <= bound;
    }
private:
    size_t bound;
};

int main()
{
    std::ifstream if1;
    if1.open("/Users/qingjie/github/CPP_Learning/cpp_primer/14p8/14p38.txt");
    test_size obj1(10);
    std::string word;
    int count_low_bound;
    int count_high_bound;
    while(if1 >> word){
        count_low_bound += obj1(word) ? 1 : 0;
    }
    //now if1 reach eof and fail flag will be set
    if1.clear();
    if1.seekg(0); //if1 go back to beginning of file


    std::cout << count_low_bound << " words in file are of sizes 1 to 10." << std::endl; //11


    count_high_bound = 0;
    count_low_bound = 0;
    test_size obj2(9);
    while(if1 >> word){
        obj2(word) ? ++count_low_bound : ++count_high_bound;
    }

    if1.close();
    std::cout << count_low_bound << " words in file are sizes of 1 to 9" << std::endl; //11
    std::cout << count_high_bound << " words in file are size of 10 or more" << std::endl; //5

    return 0;

}