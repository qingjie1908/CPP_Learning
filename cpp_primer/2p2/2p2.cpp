#include <iostream>

int reused = 42; // reused has global scope

int i = 42;

int main()
{
    int unique = 0;
    std::cout << reused << " " << unique << std::endl; //42 0

    int reused = 0;
    std::cout << reused << " " << unique << std::endl; //0 0

    std::cout << ::reused << " " << unique << std::endl; // 42 0

    int i = 100;
    int j = i;
    std::cout << j << " " << i << std::endl; //100 100

    j = ::i;
    std::cout << j << " " << i << std::endl; //42 100

    std::cout << j << " " << ::i << std::endl; //42 42

    int sum = 0;

    for (int i = 0; i != 10; ++i)
        sum += i;
    
    std::cout << i << " " << sum << std::endl; // 100 45
    std::cout << ::i << " " << sum << std::endl; // 42 45
    

    int &ri = i;
    i = 5; ri = 10; // i = 10 ri = 10
    std::cout << i << " " << ri << std::endl;
    return 0;
}