#include <functional>
#include <algorithm>
#include <map>
#include <iostream>

int add(int a, int b){
    return a + b;
}

double add(double a, double b){
    return a + b;
}

int substract(int a, int b){
    return a - b;
}

class own_add{
public:
    int operator()(int a, int b){
        return a + b + 1;
    } 
};


int main()
{
    auto f1 = [](int a, int b) -> int {return a/b;};
    std::modulus<int> obj_modulus;
    own_add obj_own_add;

    //all this callable objects has same call signature int(int, int)

    //std::function<int(int, int) function_obj can be used to represent these callable objects

    std::map<std::string, std::function<int(int, int)>> desk_calculator;

    //error, tow add function don't know which one to add
    //desk_calculator.insert({"add", add});

    std::function<int(int,int)> obj_mul = [](int a, int b)->int{return a*b;};

    int (* add_p) (int, int) = add;
    desk_calculator.insert({"add", add_p});
    desk_calculator.insert({"substract", substract});
    desk_calculator.insert({"multiply", obj_mul});
    desk_calculator.insert({"modulus", obj_modulus});
    desk_calculator.insert({"divide", f1}); //f1 is named lambda object
    desk_calculator.insert({"XOR", [](int a, int b)->int{return a^b;}}); // insert a unnamed lambda object
    desk_calculator.insert({"own_add_1", own_add()}); //insert unnamed own_add obj
    desk_calculator.insert({"own_add_2", obj_own_add}); //insert named own_add obj,

    std::cout << desk_calculator["add"](1, 2) << std::endl; //3
    std::cout << desk_calculator["substract"](1, 2) << std::endl; //-1
    std::cout << desk_calculator["multiply"](1, 2) << std::endl; //2
    std::cout << desk_calculator["modulus"](1, 2) << std::endl; //1
    std::cout << desk_calculator["divide"](1, 2) << std::endl; //0
    std::cout << desk_calculator["XOR"](1, 2) << std::endl;//3 (0b01 XOR 0b10 is 0b11, which is 0d3)
    std::cout << desk_calculator["own_add_1"](1, 2) << std::endl; //4
    std::cout << desk_calculator["own_add_2"](1, 2) << std::endl; //4

    return 0;

}