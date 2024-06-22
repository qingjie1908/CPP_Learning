#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/WordQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/OrQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/AndQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/NotQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"

//non-member func
//need access NotQuery private constructor, make it friend to class NotQuery
Query operator~(const Query& orig){
    //return Query(std::shared_ptr<Query_base>(new NotQuery(orig)));
    //below one implicitly uses the Query constructor
    return std::shared_ptr<Query_base>(new NotQuery(orig));
    //equal to following 
    //std::shared_ptr<Query_base> tmp (new NotQuery(orig))
    //return Query(tmp); //use the Query constructor that takes a shared_ptr
}

//member func
QueryResult NotQuery::eval(const TextQuery& t) const {
    QueryResult has_q = query.eval(t);

    //get whole input file size, number of lines in this file, which is used as line number check
    auto size_file = has_q.p_file->size();

    //has_q.p_result hold line number and corresponding string line,
    //line number start from 1, so check if line number is in [1, size_file]
    //note, has_q.p_result line_number is ascending order, and it's a subset of of [1, size_file]

    //so example has_q.p_result {{3, "asd"}, {5, "sdagt"}};
    //has_q.p_file is {"asf", "tty", "asd", "43ty", "sdagt", "ertqw"};
    
    //Generate a new QueryResult no_has_q, no_has_q.p_result {{1, "asf"}, {2, "tty"}, {4, "43ty"}, {6, "ertqw"}}
    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_not_result;
    auto curr = has_q.p_result->begin(); //curr refer to a pair like {3, "asd"}
    auto end = has_q.p_result->end();
    for(decltype(size_file) check_line = 1; check_line <= size_file; ++check_line){
        if(curr != end && curr->first == check_line){ //match, not add this line into new_result_vec_sp
            //advance check_line, advance curr
            ++curr;
        } else if(curr != end && curr->first != check_line) { //not match, add this line into new_result_vec_sp
            sp_new_not_result->push_back({check_line, (*(has_q.p_file))[check_line - 1]});
            //advance check_line, not doing for curr
        } else { // curr go to end; add remaning in has_q.p_file into new_result_vec_sp
            sp_new_not_result->push_back({check_line, (*(has_q.p_file))[check_line - 1]});
        }
    }

    //return new QueryResult no_has_q,
    return QueryResult(sp_new_not_result, has_q.p_occur, has_q.p_file);
}