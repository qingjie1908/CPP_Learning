#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/OrQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include <set>

Query operator|(const Query& lhs, const Query& rhs){
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& t) const{
    QueryResult lhs_result = lhs.eval(t);
    QueryResult rhs_result = rhs.eval(t);

    //lhs_result: {{1, "asa"}, {2, "bbs"}}; occur n1 times in file
    //rhs_result: {{2, "bbs"}, {3, "xwe"}}; occur n2 times in file

    //merge, and remove duplicate

    //first get merged line_number into set,
    //then use that to get string_line in input file

    std::set<int> merge_line_number;
    for(auto item : *(lhs_result.p_result)){ //item is like pair {1, "asa"}
        merge_line_number.insert(item.first);
    }
    for(auto item : *(rhs_result.p_result)){
        merge_line_number.insert(item.first);
    }
    //now set merge_line_number is 1,2,3
    //get corresponding string_line in input file (subsrcipt index is 0,1,2)

    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_or_result;

    for(auto line_number : merge_line_number){
        sp_new_or_result->push_back({line_number, (*(lhs_result.p_file))[line_number - 1]});
    }

    //for p_occrence
    std::shared_ptr<int> sp_new_or_occur;

    *sp_new_or_occur = merge_line_number.size();

    return QueryResult(sp_new_or_result, sp_new_or_occur, lhs_result.p_file);

}