#include <iostream>
#include <vector>
#include <string>
#include <functional> //for bind function

bool check_size(int x, const std::string &s1)
{
    return x > s1.size();
}

int main()
{
    std::vector<int> vec_i = {0, 3, 6, 7, 4, 9, 10};

    //find_if take unary predicate, which takes only 1 paramenter,
    //but check_size takes two paramenter
    //using bind
    std::string s = "Qingjie";
    auto bind_check_size = std::bind(check_size, std::placeholders::_1, s);

    //now bind_ckech_size will return ture if int x > 7 (s.size() is 7)
    auto iter = std::find_if(vec_i.begin(), vec_i.end(), bind_check_size);
    //now iter point to element 9

    std::cout << "first element in vec_i that has larger value than size of string \"" << s << "\" is: " << *iter << std::endl;
    //output
    //first element in vec_i that has larger value than size of string "Qingjie" is: 9

    return 0;
}