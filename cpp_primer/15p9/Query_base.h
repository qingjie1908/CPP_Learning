#ifndef QUERYBASE
#define QUERYBASE

#include <iostream>
#include <string>


class TextQuery;
class QueryResult;
class Query;




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


class Query_base{
friend class Query;
public:
    //virtual std::string rep() const = 0;
protected:
    virtual ~Query_base() = default;
   
private:
    //when we create Query q = Query("fiery") & Query("bird")
    //first Query("fiery") will construct WordQuery obj1, Query("bird") construct WordQuery obj2
    //when call obj1 obj2.eval(),
    //inside eval(), should create a TextQuery(fstream if) obj_tq, then call obj_tq.query("fiery")
    //to return a QueryResult obj1_qr; as WordQuery member
    //obj1.rep() should be "fiery"
    
    //Query::operator&(Query& obj1, Query& obj2) will return a AndQuery obj_and
    //obj_and.eval() will return its QueryResult and_r;
    //and_r.rep() should be "(fiery & bird)"
    //inside obj_and.eval(), it take obj1.member obj1.qr, and obj2.member obj2.qr
    //process obj1.qr and obj2.qr; return a new QueryResult obj as AndQuery:: member and_r
    virtual QueryResult eval(const TextQuery& obj) const = 0;

    //rep is string representation of the Query query;
    //when we call Query q = Query("fiery") & Query("bird") | Query("wind");
    //rep should return string "((fiery & bird) | wind)
    virtual std::string rep() const = 0;

    //note: we don’t intend users, or the derived classes, to use Query_base directly,
    //Query_base has no public members, All use of Query_base will be through Query objects
    //so grant class Query friendship, we store a Query_Base* p_qb in Query:: member
    //when Query q, call q.eval(), that will call p_qb->eval(); can call private member method cause we grant friendship to class Query
};

#endif
