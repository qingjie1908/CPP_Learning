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

    //if we want to order the value type also,
    //compare func can be only for key type
    //so save value in vector then sort

    
    auto curr = author_book.begin();
    while(curr != author_book.end()){

        //store values for each key in a vector
        std::vector<std::string> multimap_value_type;

        //find all element in curr key
        auto first_ele = author_book.lower_bound(curr->first);
        auto off_last_ele = author_book.upper_bound(curr->first);
        while(curr != off_last_ele){
            multimap_value_type.push_back(curr->second); //value added to value vec for the same key
            ++curr;
        }
        //now curr move to next element which key is not the same as first_ele, but equal to off_last_ele

        //now vec has original value type order b a c d, sort it
        std::sort(multimap_value_type.begin(), multimap_value_type.end(), [](std::string value1, std::string value2)->bool{return value1 > value2;});

        //now we rewrite the value from sorted vec into the multimap
        auto traverse = first_ele;
        size_t i = 0; //subscript for sorted value vec
        while(traverse != off_last_ele){
            traverse->second = multimap_value_type[i]; //write sorted d c b a into multimap value for the same key
            ++traverse;
            ++i;
        }
    }

    //now print the multimap of which the value type alsp be ordered alphabetically
    std::cout << "new multimap with value type sorted: " << std::endl;
    for(auto item : author_book){
        std::cout << "Author " << item.first << " has book : " << item.second << std::endl;
    }
    //output:
    /*
    original multimap: 
    Author C has book : b
    Author C has book : a
    Author C has book : c
    Author C has book : d
    Author B has book : b
    Author B has book : a
    Author B has book : c
    Author B has book : d
    Author A has book : b
    Author A has book : a
    Author A has book : c
    Author A has book : d
    4
    new multimap: 
    Author C has book : b
    Author C has book : a
    Author C has book : c
    Author C has book : d
    Author B has book : b
    Author B has book : a
    Author B has book : c
    Author B has book : d
    0
    new multimap with value type sorted: 
    Author C has book : d
    Author C has book : c
    Author C has book : b
    Author C has book : a
    Author B has book : d
    Author B has book : c
    Author B has book : b
    Author B has book : a
    */
}