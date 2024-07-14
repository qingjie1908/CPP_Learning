#include <bitset>
#include <vector>
#include <iostream>

void update_vecbool(std::vector<bool>& vecbool, int quesnum, bool result){
    vecbool[quesnum-1] = result;
}

int main()
{
    std::vector<int> vec1 = {1, 2, 3, 5, 8, 13, 21};

    std::bitset<32> bitvec1;

    for(auto i : vec1){
        bitvec1.set(i);
    }
    std::cout << bitvec1 << std::endl; //00000000001000000010000100101110

    //ex 17.11
    std::vector<bool> vec2(10); //10 false
    //ex 17.12
    vec2.resize(100); //100 false

    update_vecbool(vec2, 1, true); //vec2[0] is true
    update_vecbool(vec2, 2, false);
    

    //ex 17.13, one quiz 10 points
    int grade = 0;
    for(auto result : vec2){
        if(result){
            grade += 10;
        }
    }
    std::cout << grade << std::endl;//10

   


}