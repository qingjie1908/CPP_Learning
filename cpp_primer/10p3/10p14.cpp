#include <vector>
#include <iostream>
#include <string>


//int x = 2, y = 3;
int main()
{
    //==== ex 10.14 ====
    int x = 2, y = 3;
    auto f1 = [x, y]() -> int {return x + y;};
    //f surround function is main(), it can be nested
    //so it needs to include x,y in capture list to be used in its function body
    //if x, y are defined out side of main and is in the scope where main apprear,
    //it does not need to include x,y in capture list
    std::cout << f1() << std::endl; //5

    //==== ex 10.15 ====
    int m = 4;
    auto f2 = [m] (int para) -> int {return m + para;};
    std::cout << f2(7) << std::endl; //11
}