#include <iostream>
#include <string>
#include <vector>

int main()
{
    int local_v = 5;
    //explicit caputre: auto f = [&local_v]() -> bool {...}
    auto f = [&]() -> bool { //implicit capture
        if(local_v){ //local_v not 0
            --local_v;
            return false;
        } else { //local_v is 0
            return true;
        }
    };

    // f is an object, takes refence to local_v in function body

    //first check if function body excute when we create object f
    std::cout << "after create object f from lambda expression, local_v is: " << local_v << std::endl;
    //5, which means create object f not excute function body

    // call f until local_v is 0
    while(!f()){// if local_v not 0, f() return false, and also decreament local_v
        f();
        std::cout << "local_v now is: " << local_v << std::endl;
    }

    std::cout << "local_v final value is: " << local_v << std::endl;

    //output
    /*
    after create object f from lambda expression, local_v is: 5
    local_v now is: 3
    local_v now is: 1
    local_v now is: 0
    local_v final value is: 0
    */

}