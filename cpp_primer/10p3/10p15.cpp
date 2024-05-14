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

    //sort words by size, and maintain original alphabetical order for the same size elements
    //so the predicates will compare two elements' size
    //here predicate is callable unit
    //which is a lambda function auto f = [](const string &s1, const string &s2){return s1.size() < s2.size()};
    //when call this unit f(s1, s2); it will pass two element from words into s1 and s2
    std::stable_sort(words.begin(), words.end(), [](const std::string &s1, const std::string &s2){return s1.size() < s2.size();});

    //now get an iter to the first element whose size() is >= sz
    //since for find_if, it only take one parameter for predicates
    //use lambda expression to include sz into capture list, one parameter would be the element in the words vector
    auto iter = std::find_if(words.begin(), words.end(), [sz](const std::string &s){return s.size() >= sz;});

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