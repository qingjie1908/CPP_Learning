#include <map>
#include <set>
#include <string>
#include <vector>
#include <iostream>

int main()
{
    std::map<std::string, size_t> word_count;

    std::vector<std::string> vec_s = {  "ex", "ex,", "Ex",
                                        "abc", "Abc", "abc,",
                                        "not", "NOT",
                                        "this"};

    auto iter = vec_s.begin();

    while(iter != vec_s.end()){
        ++word_count[*iter];
        ++iter;
    }

    //now print each element
    for(auto item : word_count){
        std::cout << item.first << " occurs " << item.second << ((item.second > 1) ? "times." : "time.") << std::endl;
    }
    //output in alphabetical order
    /*
    Abc occurs 1time.
    Ex occurs 1time.
    NOT occurs 1time.
    abc occurs 1time.
    abc, occurs 1time.
    ex occurs 1time.
    ex, occurs 1time.
    not occurs 1time.
    this occurs 1time.
    */

    //==== ex 11.4 ====
    //first empty word_count in previous code
    word_count.clear();
    std::set<char> set_punc_case = {',', '.'};
    iter = vec_s.begin();

    while (iter != vec_s.end()){
        if(set_punc_case.find(iter->back()) != set_punc_case.end()){
            iter->pop_back(); //string element pop out the punctuation in this set
        }
        if(isalpha(iter->front())){//first char in string
            (*iter)[0] = tolower((*iter)[0]); //change first char to lower
        }
        ++word_count[*iter]; //like word_count[ex] = 1; if previously no ex
        ++iter;
    }

    for (auto item : vec_s){
        std::cout << item << " ";
    }
    std::cout << std::endl;
    //ex ex ex abc abc abc not nOT this 

    //now print each element
    for(auto item : word_count){
        std::cout << item.first << " occurs " << item.second << ((item.second > 1) ? "times." : "time.") << std::endl;
    }
    /*
    abc occurs 3times.
    ex occurs 3times.
    nOT occurs 1time.
    not occurs 1time.
    this occurs 1time.
    */


    

}