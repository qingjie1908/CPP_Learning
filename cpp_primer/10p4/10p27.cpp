#include <iostream>
#include <vector>
#include <string>
#include <list>

int main()
{
    std::vector<std::string> vec_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    std::vector<std::string> vec_s2;
    std::vector<std::string> vec_s3;
    std::list<std::string> lst_1;


    //unique copy only check consecutive two elements and move duplicated one to last
    //need to sort alphabetically first to make same elements consecutive
    std::sort(vec_s.begin(), vec_s.end()); //default predicates use < operator

    //back_inserter behave like push_back
    std::unique_copy(vec_s.begin(), vec_s.end(), std::back_inserter(vec_s2));

    //first loop: inserter point to vec_s3.begin(), insert "the" before this inserter, then inserter still point to orginal add position, which now point to after "the"
    //second loop; inserter point after "the", insert "quick" before this inserter, now inserter point to after "quick"
    std::unique_copy(vec_s.begin(), vec_s.end(), std::inserter(vec_s3, vec_s3.begin()));

    std::unique_copy(vec_s.begin(), vec_s.end(), std::inserter(lst_1, lst_1.begin()));


    for(auto item : vec_s2)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    for(auto item : vec_s3)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    for(auto item : lst_1)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //output
    /*
    fox jumps over quick red slow the turtle 
    fox jumps over quick red slow the turtle 
    fox jumps over quick red slow the turtle 
    */
    return 0;
}