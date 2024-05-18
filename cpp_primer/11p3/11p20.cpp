#include <map>
#include <iostream>

int main()
{
    std::map<std::string, size_t> word_count;
    std::string word;
    while(std::cin >> word){
        auto iter = word_count.insert({word, 1});
        //iter return by insert() is a pair,
        //iter.first is the iter denote the element, which is a map iterator re-
        //ferring to the element with the given key. not the element we insert; 
        //second is bool indicate insert successful
        //for map, each key is unique, it will return false it there is duplicate, and insert() do nothing

        if(!iter.second){ // which means key duplicate,
            //iter.first is iter denote the element in map
            (*(iter.first)).second += 1;
        }

        //same effect with follow one command
        //++word_count.insert({word, 0}).first->second;
    }

    for (auto item : word_count){
        std::cout << item.first << " occurs " << item.second << (item.second > 1 ? "times." : "time.") << std::endl;
    }
    //input: a aa ab aa aa
    /*output
    a occurs 1time.
    aa occurs 3times.
    ab occurs 1time.
    */


}