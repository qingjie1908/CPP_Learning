#include <iostream>
#include <list>
#include <string>

void elimDups(std::list<std::string> &lst)
{
    //sort words alphabetically
    lst.sort(); //default predicate use < operator
    
    //print original size
    std::cout << "original list size: " << lst.size() << std::endl;

    //list version unique will remove the duplicates, means list.size() change
    //generic version unique not change container size
    lst.unique(); //unary predicate, default use == operator

    std::cout << "list size after list version unique algorithm: " << lst.size() << std::endl;

    //so we dont need to erase after list version unique
}

int main()
{
    std::list<std::string> lst_s = {"the", "quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};

    elimDups(lst_s);
    

    //print lst
    for(auto item : lst_s){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}