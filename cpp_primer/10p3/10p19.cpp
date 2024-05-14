#include <iostream>
#include <string>
#include <vector>

//put vector of string in alphabetical order and remove duplicates
void elimDups(std::vector<std::string> &vec_s)
{
    std::sort(vec_s.begin(), vec_s.end()); //this will use default predicates which is < operator between vector elements
    //now vec_s are in alphabetical order

    //remove duplicate elements
    auto iter = std::unique(vec_s.begin(), vec_s.end());
    //iter now point to first element of the second part of vec_s;
    //the second part of vec_s are all duplicated elements
    //erase them

    while(iter != vec_s.end()){
        iter = vec_s.erase(iter); //return iter point to next element after the erased one
    }
}



void biggies(std::vector<std::string> &words, std::vector<std::string>::size_type sz)
{
    elimDups(words);

    //now words are in alphabetical order with no duplicates

    //use partition instead of find_if
    //iter returns the one past element's iter of the firt part's last element
    //element's predicates returns true is in first part
    auto iter = std::stable_partition(words.begin(), words.end(), [sz](const std::string &s){return s.size() < sz;});

    //how many element has size larger than sz?
    auto count = words.end() - iter;
    std::cout << "There are " << count << " element in this string vector whose size is larger than " << sz << "." << std::endl;

    //now print all these larger size elements
    //for_each will call the callable unit, here is the lambda func
    //on each element in the range, the element here is string, not iter
    //so the parameter list is &string
    //since the lambda func no return , then it returns void
    std::for_each(iter, words.end(), [](const std::string &s){std::cout << s << " ";});

    std::cout << std::endl;
}

int main()
{
    std::vector<std::string> vec_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    decltype(vec_s.size()) want_size = 5;
    biggies(vec_s, want_size);
    //jumps quick turtle

}