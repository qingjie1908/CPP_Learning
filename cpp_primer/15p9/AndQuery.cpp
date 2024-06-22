#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/WordQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/OrQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/AndQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/NotQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"
#include <set>
#include <algorithm> //set intersection
#include <iterator>

Query operator&(const Query& lhs, const Query& rhs){
    //generator a AndQuery object, use &AndQuery to construct a Query object hold AndQuery pointer
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));  
}

QueryResult AndQuery::eval(const TextQuery& t) const{
    QueryResult lhs_result = lhs.eval(t);
    QueryResult rhs_result = rhs.eval(t);

    //lhs_result: {{1, "asa"}, {2, "bbs"}}; occur n1 times in file
    //rhs_result: {{2, "bbs"}, {3, "xwe"}}; occur n2 times in file

    //And only get {{2, "bbs"}} into new result

    std::set<int> lhs_line_number, rhs_line_number;
    for(auto item : *(lhs_result.p_result)){ //item is like pair {1, "asa"}
        lhs_line_number.insert(item.first);
    }
    for(auto item : *(rhs_result.p_result)){
        rhs_line_number.insert(item.first);
    }
    //now set lhs and rhs set is {1, 2} and {2, 3}
    //get final set {2}
    std::set<int> new_and_set;

    std::set_intersection(lhs_line_number.begin(), lhs_line_number.end(), rhs_line_number.begin(), rhs_line_number.end(),
                            std::inserter(new_and_set, new_and_set.begin()));

    //now new_and_set is {2}, push_back input file index at 1

    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_or_vec_result;
    for (auto line_number : new_and_set){
        sp_new_or_vec_result->push_back({line_number, (*(lhs_result.p_file))[line_number - 1]});
    }

    std::shared_ptr<int> sp_new_and_occur;
    (*sp_new_and_occur) = new_and_set.size();

    return QueryResult(sp_new_or_vec_result, sp_new_and_occur, lhs_result.p_file);
}