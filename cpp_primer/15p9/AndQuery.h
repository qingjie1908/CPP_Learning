#ifndef ANDQUERY
#define ANDQUERY

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

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/BinaryQuery.h"

class AndQuery : public BinaryQuery {
friend Query operator&(const Query& lhs, const Query& rhs); //need to create AndQuery obj in this func, access to its protected cosntructor
public:

protected:
    //inhereited virtual destructor

    AndQuery(const Query& lhs_p, const Query& rhs_p):BinaryQuery(lhs_p, rhs_p, "&"){std::cout << "AndQuery::constrcut" << std::endl;}

    QueryResult eval(const TextQuery& t) const override;
    //eval() will use inherited lhs and rhs QueryResult, no need add Query lhs and rhs member in this class, included in BinaryQuery class

    //we do not need to override rep() in AndQuery class, then we we call Query_Base_sp->rep(), which dynamic type is AndQuery
    //first it will look up name rep() in AndQuery class, not override, so use inherited version from BinaryQuery class
    //if rep() in BinaryQuery is private, then it will be private in AndQuery, so Query_Base_sp->rep() is in-accessiable
    //so rep() need to be in BinaryQuery::protected region

    //ex 15.37
    //if member is not Query query; but shared_ptr<Query_base> sp
    //no change for AndQuery, use BinaryQuery constructor to intialized the shared_ptr member
   
private:

};


#endif