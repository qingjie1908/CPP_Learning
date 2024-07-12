#ifndef QUERYRESULT
#define QUERYRESULT

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <limits>
#include <tuple>


typedef std::tuple<std::shared_ptr<std::vector<std::pair<int, std::string>>>, std::shared_ptr<int>, std::shared_ptr<std::vector<std::string>>, int> QueryResult;

// class QueryResult{
// friend std::ostream& print(std::ostream& os, QueryResult& result_obj, int range_low, int range_high);

// public:
//     //constructor
//     //p_tq is the shared pointer in TextQuery class
//     QueryResult(std::shared_ptr<std::vector<std::pair<int, std::string>>> p_tq, std::shared_ptr<int> p_oc, std::shared_ptr<std::vector<std::string>> p_f, int i): 
//                 p_result(p_tq), p_occur(p_oc), p_file(p_f), check_type(i){}

//     QueryResult():p_result(std::make_shared<std::vector<std::pair<int, std::string>>>()), 
//                   p_occur(std::make_shared<int>(0)),
//                   p_file(std::make_shared<std::vector<std::string>>()),
//                   check_type(1){
//         //can use make_shared here cause QueryResult constructor is public
//         //if constructor is private, use new() in member initializer list
//         //default constructor point to empty vec
//         //default constructor occur hold 0
//         //default constructor pfile hold empty vec
//     } 
    
    
// private:
//     //shared_ptr to hold a result vec, element is a pair <line number, line_string>
//     std::shared_ptr<std::vector<std::pair<int, std::string>>> p_result;

//     //p_occur hold count of how many times requrest word appear in the file
//     std::shared_ptr<int> p_occur;

//     //share_ptr to hold the whole original input file for TextQuery
//     //need this to find the NotQuery part
//     std::shared_ptr<std::vector<std::string>> p_file;

//     //after a TextQuery obj call obj.query(word), p_result may have results or a nullptr

//     int check_type;

// };

std::ostream& print(std::ostream& os, QueryResult& result_obj, int range_low = 1, int range_high = std::numeric_limits<int>::max());
//declare this as non-freind with default argument
//then define this in .cpp, inside .cpp defination cannot have default arguments again

#endif