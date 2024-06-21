#ifndef QUERYRESULT
#define QUERYRESULT

#include <iostream>
#include <string>
#include <memory>
#include <vector>

class QueryResult{
friend std::ostream& print(std::ostream& os, QueryResult& result_obj);
friend class NotQuery;
friend class OrQuery;
friend class AndQuery;
public:
    //constructor
    //p_tq is the shared pointer in TextQuery class
    QueryResult(std::shared_ptr<std::vector<std::pair<int, std::string>>> p_tq, std::shared_ptr<int> p_oc, std::shared_ptr<std::vector<std::string>> p_f): p_result(p_tq), p_occur(p_oc), p_file(p_f) {}

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

    //share_ptr to hold the whole original input file for TextQuery
    //need this to find the NotQuery part
    std::shared_ptr<std::vector<std::string>> p_file;



    //after a TextQuery obj call obj.query(word), p_result may have results or a nullptr

};

#endif