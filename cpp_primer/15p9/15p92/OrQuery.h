#ifndef ORQUERY
#define ORQUERY

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

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/BinaryQuery.h"

class OrQuery : public BinaryQuery {
friend Query operator|(const Query& lhs, const Query& rhs);
public:

protected:
    ~OrQuery(){std::cout << "~OrQuery()" << std::endl;}

    OrQuery(const Query& lhs_p, const Query& rhs_p):BinaryQuery(lhs_p, rhs_p, "|"){std::cout << "OrQuery::construct." << std::endl;}

    QueryResult eval(const TextQuery& t) const override;

    //use inherited rep() from BinaryQuery

    //ex 15.37
    //if member is not Query query; but shared_ptr<Query_base> sp
    //no change for OrQuery, use BinaryQuery constructor to intialized the shared_ptr member

    OrQuery* clone() const & override {return new OrQuery(*(this));}
    OrQuery* clone() && override {return new OrQuery(std::move(*this));}

private:
};

#endif