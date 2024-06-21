#ifndef BINARYQUERY
#define BINARYQUERY

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
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"

class BinaryQuery : public Query_base{
public:

protected:
    //virtual destructor inherited here

    BinaryQuery(const Query& lhs_p, const Query& rhs_p, const std::string& opSym_p):lhs(lhs_p), rhs(rhs_p), opSym(opSym_p){std::cout << "BinaryQuery::construct." << std::endl;}

    //these are virtual in Query_base, no need add virtual specifier again
    //QueryResult eval(const TextQuery& obj) const = 0;
    std::string rep() const override {
        std::cout << "BinaryQuery::rep()" << std::endl;
        return lhs.rep() + " " + opSym + " " + rhs.rep();
    }

    //we did not add QueryResult eval(const TextQuery& t) const override; in this class
    //so BinaryQuery class does not define eval() and so inherits a pure virtual.
    //Thus, BinaryQuery is also an abstract base class, and we cannot create objects of BinaryQuery type.
    //AndQuery and OrQuery will use BinaryQuery constructor to construct AndQuery and OrQuery object,
    //so BinaryQuery constrcutor should be protected, not private

    //we do not need to override rep() in AndQuery class, then we we call Query_Base_sp->rep(), which dynamic type is AndQuery
    //it will look up name rep() in AndQuery class, not override, so use inherited version from BinaryQuery class
    //if rep() in BinaryQuery is private, then it will be private in AndQuery, so Query_Base_sp->rep() is in-accessiable
    //so rep() need to be in BinaryQuery::protected region

    //follow also in protected not in private, cause AndQuery and OrQuery inherit these two and need access them
    Query lhs;
    Query rhs;
    std::string opSym; // name of binary operator, like "&" or "|"

    //ex 15.37
    //if member is not Query query; but shared_ptr<Query_base> sp
    //need make BinaryQuery friend to class Query to access lhs_p.sp_qb (private member sp_qb)
    //need Query_base::rep() to be public so that sp_lhs->rep() can have access
    // std::shared_ptr<Query_base> sp_lhs, sp_rhs;
    // BinaryQuery(const Query& lhs_p, const Query& rhs_p, const std::string& opSym_p):sp_lhs(lhs_p.sp_qb), sp_rhs(rhs_p.sp_qb), opSym(opSym_p){}
    // std::string rep() const override {return sp_lhs->rep() + " " + opSym + " " + sp_rhs->rep();}

private:

    
};

#endif