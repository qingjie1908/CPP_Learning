#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/WordQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"


QueryResult WordQuery::eval(const TextQuery& t) const {
    QueryResult ret = t.query(query_word);
    return ret;
}

std::string WordQuery::rep() const{
    return query_word;
}