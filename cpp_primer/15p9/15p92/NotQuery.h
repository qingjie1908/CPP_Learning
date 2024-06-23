#ifndef NOTQUERY
#define NOTQUERY

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

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/Query_base.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/Query.h"
class NotQuery : public Query_base{
public:
friend class Query; //Query need access, Query q, ~q will return sp_qb hold address of new NotQuery obj
friend Query operator~(const Query& orig); //need access NotQuery private constructor
protected:
    //inherited virtual constructor
    ~NotQuery(){
        std::cout << "~NotQuery()" << std::endl;
    }

    //Explicitly-defined copy constructors do not call copy constructors for the members.
    /*
    NotQuery(const NotQuery& orig){
        query = orig.query; //wrong, this copy constructor explictly called, so in its member initialzied list, member query will be initialized
        //since here no member initialized list, so query will be default initialized, but query has no default constructor, error
    }
    */

   //if not explicity defind our own NotQuery(const NotQuery& orig)
   //then when return new NotQuery(*this); it will call systhesized NotQuery::copy_construct
   //which will call Query::copy_construct (user_defined n Query)


private:

    NotQuery(const Query& obj):query(obj){std::cout << "NotQuery::construct" << std::endl;} //private constrcutor for NotQuery

    QueryResult eval(const TextQuery& t) const override;
    std::string rep() const override {
        std::cout << "NotQuery::rep()" << std::endl;
        return "~(" + query.rep() + ")";
        // call to rep in NotQuery’s own rep member ulti- mately makes a virtual call to rep: query.rep(), a nonvirtual call to the rep member of the Query class
        // Query::rep in turn calls q->rep(), which is a vir- tual call through its Query_base pointer
    }
    
    Query query;

    //ex 15.37
    //if member is not Query query; but shared_ptr<Query_base> sp
    // std::shared_ptr<Query_base> sp_not;
    // //rep() should be public in class Query_Base
    // std::string rep() const override {return "~(" + sp_not->rep() + ")";}

    NotQuery* clone() const & override { return new NotQuery(*this);} //call systhesized version of NotQuery::copy constrol, then call query::copy_control, then call clone, finally will call to WordQuery.clone
    NotQuery* clone() && override {return new NotQuery(std::move(*this));}
};

#endif