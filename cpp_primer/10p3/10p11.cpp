#include <iostream>
#include <string>
#include <vector>

void elimDups(std::vector<std::string> &vec)
{
    //first, sort the string so that dupicates appera adjacent in the vector
    std::sort(vec.begin(), vec.end());

    //print sorted vec
    std::cout << "sorted string vec are: " << std::endl;
    for(auto item : vec){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //now use unique to so that each word appears once in the
    // front portion of the range and returns an iterator one past the unique range
    auto end_unique = std::unique(vec.begin(), vec.end());

    //vec size is not changed by uniq(), print vec now
    std::cout << "sorted string vec with only unique value in the front portion has size: " << vec.size() << std::endl;
    std::cout << "sorted string vec with only unique value in the front portion are: " << std::endl;
    for(auto item : vec){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //now earse the duplicates after the end_unique iter (including this)
    vec.erase(end_unique, vec.end()); //if end_unique = vec.end(), then the range is empty since iter range are left inclusive
    //[ vec.end(),  vec.end() ) means empty range, takes no effect

    //now print the size changed vec
    std::cout << "sorted string vec with duplicates erased are: " << std::endl;
    for(auto item : vec){
        std::cout << item << " ";
    }
    std::cout << std::endl;

}

bool is_shorter(const std::string &s1, const std::string &s2)
{
    return s1.size() < s2.size();
}

int main()
{
    std::vector<std::string> vec_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    elimDups(vec_s);
    //now vec_s is:
    //fox jumps over quick red slow the turtle

    //we want to sort by size use predicates is_shorter (if not defined predicates, then sort use < operator between element by default)
    //then for the same size, they are considered equal in terms of this predicates
    //but we want to maintain the orginal alphabetical order we have done in elimDups between these equal(same size) elemets
    //then we use stable sort
    std::stable_sort(vec_s.begin(), vec_s.end(), is_shorter);

    //now print the vec_s
    for(auto item : vec_s){
        std::cout << item << " ";
    }
    std::cout << std::endl;
    //fox red the over slow jumps quick turtle

}