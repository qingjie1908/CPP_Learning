#include "/Users/qingjie/github/CPP_Learning/cpp_primer/16p1/Screen.h"

int main()
{
    Screen<3, 4> obj1;

    std::cout << obj1 << std::endl;

    obj1.get(1, 2);

    obj1.set('a');

    obj1.set(2, 3, 'b');

    while(std::cin >> obj1){
        std::cout << obj1 << std::endl;
    }

    return 0;



}