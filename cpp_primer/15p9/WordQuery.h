#ifndef WORDQUERY
#define WORDQUERY

/*
                ┌──────────┐                      
                │Query_base│                      
                └────┬─────┘                      
                     │                            
     ┌───────────────┼────────────────┐           
     │               │                │           
┌────▼────┐      ┌───▼────┐     ┌─────▼─────┐     
│WordQuery│      │NotQuery│     │BinaryQuery│     
└─────────┘      └────────┘     └──┬──────┬─┘     
                                   │      │       
                                   │      │       
                            ┌──────▼─┐   ┌▼──────┐
                            │AndQuery│   │OrQuery│
                            └────────┘   └───────┘
*/

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query_base.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"
class Query;
class QueryResult;

class WordQuery : public Query_base {
friend class Query; //since eval and rep are private, need to made friend, cause Query::sp_qb->eval() need
//also, Query need WordQuery constrctor
public:
    
protected:
    //inherite default virtual constructor from Query_base

private:
    WordQuery(const std::string& sp):query_word(sp){std::cout << "WordQuery(string)." << std::endl;}

    QueryResult eval(const TextQuery& t) const override {return t.query(query_word);}
    std::string rep() const override {std::cout << "Wordquery::rep()" << std::endl; return query_word;}

    std::string query_word;

};


#endif