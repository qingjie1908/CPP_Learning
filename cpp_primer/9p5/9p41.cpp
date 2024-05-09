#include <iostream>
#include <string>
#include <vector>

int main()
{
    //==== ex 9.41 ====
    std::vector<char> vec_c = {'a', 'c', 's', 't', 'w'};
    
    auto begin = vec_c.begin();
    auto end = vec_c.end();

    std::string s1(begin, end);

    std::cout << "s1.size(): " << s1.size() << std::endl;
    std::cout << s1 << std::endl;

    // ==== ex 9.42 ====
    std::string s2;
    for(int i = 0; i < 100; ++i){
        char c;
        //char 8 bit, value [0,255]
        /*
        if generate number between 5 to 10 for example
        5 to 10: total 6 ints
        rand()%6 // get 6 rand ints : 0, 1, 2, 3, 4, 5, 
        rand()%6 +5 is 6 rand ints between 5 to 10
        so generally, get rand ints between upper and lower
        rand()%(upper-lower+1) + lower 
        */
        // A-Z : 65 - 90
        // a-z : 97 - 122
        c = rand()%(90-65+1) + 65; // c is random char between A to Z
        s2.push_back(c);
    }

    std::cout << "s2.size(): " << s2.size() << std::endl;
    std::cout << s2 << std::endl;

    return 0;
    
}