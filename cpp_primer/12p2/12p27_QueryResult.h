#ifndef QUERYRESULT
#define QUERYRESULT

#include <iostream>
#include <string>
#include <memory>
#include <vector>

class QueryResult{
friend std::ostream& print(std::ostream& os, QueryResult& result_obj);
public:
    //constructor
    //p_tq is the shared pointer in TextQuery class
    QueryResult(std::shared_ptr<std::vector<std::pair<int, std::string>>> p_tq, std::shared_ptr<int> p_oc): p_result(p_tq), p_occur(p_oc) {}

    QueryResult(){
        //default constructor point to empty vec
        p_result = std::make_shared<std::vector<std::pair<int, std::string>>>();

        //default constructor occur hold 0
        p_occur = std::make_shared<int>(0);

    } 
    
    
private:
    //shared_ptr to hold a result vec, element is a pair <line number, line_string>
    std::shared_ptr<std::vector<std::pair<int, std::string>>> p_result;

    //p_occur hold count of how many times requrest word appear in the file
    std::shared_ptr<int> p_occur;



    //after a TextQuery obj call obj.query(word), p_result may have results or a nullptr

};

//non-member func print
std::ostream& print(std::ostream& os, QueryResult& result_obj){
    //first check if there is any result
    if(!result_obj.p_result->empty()){
        //first print the word occurence in the whole file
        os << "element occurs " << *result_obj.p_occur << " times: " << std::endl;

        //then print each line that contains this word
        auto curr = result_obj.p_result->begin();
        while(curr != result_obj.p_result->end()){
            os << "\t" << "(line " << curr->first << ") " << curr->second << std::endl;
            ++curr;
        }
    } else {
        os << "not find this element." << std::endl;
    }
    return os;
}



#endif