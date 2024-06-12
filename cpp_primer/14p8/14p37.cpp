#include <iostream>
#include <vector>
#include <algorithm>


class euqal_check{
public:
    euqal_check(int check_value_p = 0):check_value(check_value_p){}
    bool operator()(const int x){
        return x == check_value;
    }
private:
    int check_value;
};

int main()
{
    std::vector<int> vec1 = {1, 0, 3, 7, 7, 5, 9, 0};

    std::replace_if(vec1.begin(), vec1.end(), euqal_check(), 4); //hear eqaul_check() is create an obj, not call obj

    //here it's like we first create equal_check obj, since we did not pass argument, then its like equal_check obj(0), check_value = 0
    //then replace_if call this obj, pass *iter as argument, so obj(*iter); now return bool *iter == 0 , then replace to 4 if its true

    for(auto item : vec1){
        std::cout << item << " ";
    }
    std::cout << std::endl; //1 4 3 7 7 5 9 4

    std::replace_if(vec1.begin(), vec1.end(), euqal_check(7), 77);

    for(auto item : vec1){
        std::cout << item << " ";
    }
    std::cout << std::endl; //1 4 3 77 77 5 9 4

    return 0;
}
