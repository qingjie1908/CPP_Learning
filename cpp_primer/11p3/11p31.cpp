#include <map>
#include <vector>
#include <iostream>
#include <string>

bool compare_key_value (std::string key1, std::string key2)
{
    return key1 > key2;
    
}

int main()
{
    std::multimap<std::string, std::string, decltype(compare_key_value) *> author_book(compare_key_value);

    std::vector<std::string> authors = {"B", "A", "C"};
    std::vector<std::string> books = {"b", "a", "c", "d"};

    for(auto author : authors){
        for(auto book : books){
            author_book.insert({author, book});
        }
    }

    //orgirnal map
    std::cout << "original multimap: " << std::endl;
    for(auto item : author_book){
        std::cout << "Author " << item.first << " has book : " << item.second << std::endl;
    }

    auto count = author_book.erase("A"); //return count of removed 
    std::cout << count << std::endl; //4

    //error example:
    /*
    for(auto begin = author_book.lower_bound("A"), end = author_book.upper_bound("A"); begin != end; ++begin){
        author_book.erase(begin);
        //iterators to the erased elements are invalidated
        //++begin then dereference is disaster
    }
    */

    //below is ok
    //author_book.erase(author_book.lower_bound("A"), author_book.upper_bound("A"));
    
    std::cout << "new multimap: " << std::endl;
    for(auto item : author_book){
        std::cout << "Author " << item.first << " has book : " << item.second << std::endl;
    }
    
    count = author_book.erase("A"); //now count = 0
    std::cout << count << std::endl;
    //output:
    // original multimap: 
    // Author A has book : b
    // Author A has book : a
    // Author A has book : c
    // Author A has book : d
    // Author B has book : b
    // Author B has book : a
    // Author B has book : c
    // Author B has book : d
    // Author C has book : b
    // Author C has book : a
    // Author C has book : c
    // Author C has book : d
    // new multimap: 
    // Author B has book : b
    // Author B has book : a
    // Author B has book : c
    // Author B has book : d
    // Author C has book : b
    // Author C has book : a
    // Author C has book : c
    // Author C has book : d

    //reorder by compare_key_value output:
    // original multimap: 
    // Author C has book : b
    // Author C has book : a
    // Author C has book : c
    // Author C has book : d
    // Author B has book : b
    // Author B has book : a
    // Author B has book : c
    // Author B has book : d
    // Author A has book : b
    // Author A has book : a
    // Author A has book : c
    // Author A has book : d
    // 4
    // new multimap: 
    // Author C has book : b
    // Author C has book : a
    // Author C has book : c
    // Author C has book : d
    // Author B has book : b
    // Author B has book : a
    // Author B has book : c
    // Author B has book : d
    // 0
}