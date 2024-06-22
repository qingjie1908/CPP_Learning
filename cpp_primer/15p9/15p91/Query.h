#ifndef QUERY
#define QUERY

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <memory>
#include <fstream>
#include <sstream>
#include <iterator>

class QueryResult;

class TextQuery{
friend void generate_vec_file(std::ifstream& in_f, std::vector<std::string>& vec_f);
friend void generate_map(std::vector<std::string>& vec_r, std::set<int>& line_record_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r);
//friend class QueryResult;
public:
    //constructor declaration, using ifstream to store the input file
    TextQuery(std::ifstream &input_f);

    //member func query(), to find the line for given word
    //return a QueryResult obj
    QueryResult query(const std::string& find_word) const;

private:
    std::ifstream& input_file; //note when we pass stream as constructor element, it's a reference, cannot copy

    //first, need to store the file into vector line by line, this is done in constructor
    //we want to share this with QueryResult also, so that we can use this to find the NotQuery part (whole vec - match vec)
    std::shared_ptr<std::vector<std::string>> vec_file_sp;

    std::set<int> line_record; //hold the line numbers on which each word appears
    std::map<std::string, std::set<int>> word_line_map; //map, word and its corresponding set holding line number on which word appear
    std::map<std::string, int> word_count_map; //map, word and its occurrence in the file

};

class QueryResult{
friend std::ostream& print(std::ostream& os, QueryResult& result_obj);
friend class NotQuery;
friend class OrQuery;
friend class AndQuery;
public:
    //constructor
    //p_tq is the shared pointer in TextQuery class
    QueryResult(std::shared_ptr<std::vector<std::pair<int, std::string>>> p_tq, std::shared_ptr<int> p_oc, std::shared_ptr<std::vector<std::string>> p_f): 
                p_result(p_tq), p_occur(p_oc), p_file(p_f){}

    QueryResult():p_result(std::make_shared<std::vector<std::pair<int, std::string>>>()), 
                  p_occur(std::make_shared<int>(0)),
                  p_file(std::make_shared<std::vector<std::string>>()){
        //can use make_shared here cause QueryResult constructor is public
        //if constructor is private, use new() in member initializer list
        //default constructor point to empty vec
        //default constructor occur hold 0
        //default constructor pfile hold empty vec
    } 
    
    
private:
    //shared_ptr to hold a result vec, element is a pair <line number, line_string>
    std::shared_ptr<std::vector<std::pair<int, std::string>>> p_result;

    //p_occur hold count of how many times requrest word appear in the file
    std::shared_ptr<int> p_occur;

    //share_ptr to hold the whole original input file for TextQuery
    //need this to find the NotQuery part
    std::shared_ptr<std::vector<std::string>> p_file;

    //after a TextQuery obj call obj.query(word), p_result may have results or a nullptr

};

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

class Query{
friend Query operator~(const Query& orig); //return a Query obj, obj.member shared_ptr<Query_Base>* point to a NotQuery object 
friend Query operator|(const Query& lhs, const Query& rhs); //return a Query obj, obj.member shared_ptr<Query_Base>* point to a OrQuery object 
friend Query operator&(const Query& lhs, const Query& rhs); //return a Query obj, obj.member shared_ptr<Query_Base>* point to a AndQuery object
//inside these operator function, we create for example AndQuery obj, when we return it, we return the AndQuery obj pointer, so we use a pointer to construct return Query obj
//so Query class need a construct that takes a std::shared_ptr<Query_base>

public:
    Query(const std::string& s);
    /*
    Query(const std::string& s):sp_qb(new WordQuery(s)){

        //sp_qb(std::make_shared<WordQuery>(s)) is wrong, cause make_shared is a class, cannot access WordQuery Private constructor even class Query is friend of class WordQuery cause make_shared itself not friend of class WordQuery
        //std::make_shared has no access to the privates of MyClass. It's outside the scope of Class Query
        //should use sp_qb(new WordQuery(s)), cause new is a lambda function

        //The new is actually used within a lambda in a member-function; 
        //A lambda defines a local-class, and C++ standards permits a local-class within a member-function to access everything the member-function can access.
        //And its trivial to remember that member functions can access privates.. here class Query is friend of class WordQuery
        
        //do not initialize in constructor body
        
        public : Thing(int _foo, int _bar){
            member1 = _foo;
            member2 = _bar;
        }
        is equivalent to

        public : Thing(int _foo, int _bar) : member1(), member2(){
            member1 = _foo;
            member2 = _bar;
        }
        because they will be initialized before the constructor body starts executing, 
        so basically twice the work is done. 
        That also means, if the type of these members don't have default constructor, then your code will not compile.
        

        std::cout << "Query(string)" << std::endl;
    } //this will construct a WordQuery obj, and bind it to sp_pb;
    */

    //below is ok WordQuery * q= new WordQuery(s), sp_qb(q) is ok (initialization) p can be converted to sp_qb, sp_qb = q is wrong, type mismatch 
    // inline
    // Query::Query(const std::string &s): sp_qb(new WordQuery(s)) { }


    QueryResult eval(const TextQuery& t ) const {return sp_qb->eval(t);} //call virtual eval() in Query_base, dynamic binding, default inline
    std::string rep() const {std::cout << "Query::rep()" << std::endl; return sp_qb->rep();} //call virtual rep() in Query_base, dynamic binding, define inside class, default inline

private:
    //constructor to take std::shared_ptr<Query_base> cause operator return pointer to And/Or/NorQuery object
    //we make it private cause we will not use Query_base and derived class to constrcut Query in user code
    //Query_base and derived class are implementation class for Query; so that's why we need to friend operator overloaed function, they need to access private constrcutor
    Query(std::shared_ptr<Query_base> sp_p):sp_qb(sp_p){std::cout << "Query(sp)" << std::endl;} // default inline
    std::shared_ptr<Query_base> sp_qb;
};

inline
std::ostream& operator<<(std::ostream& os, const Query& q){return os << q.rep();}



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

//public constructor of Query::
inline
Query::Query(const std::string &s): sp_qb(new WordQuery(s)) {std::cout << "Query(string)." << std::endl;}


class NotQuery : public Query_base{
public:
friend class Query; //Query need access, Query q, ~q will return sp_qb hold address of new NotQuery obj
friend Query operator~(const Query& orig); //need access NotQuery private constructor
protected:
    //inherited virtual constructor

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

};

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

class OrQuery : public BinaryQuery {
friend Query operator|(const Query& lhs, const Query& rhs);
public:

protected:
    OrQuery(const Query& lhs_p, const Query& rhs_p):BinaryQuery(lhs_p, rhs_p, "|"){std::cout << "OrQuery::construct." << std::endl;}

    QueryResult eval(const TextQuery& t) const override;

    //use inherited rep() from BinaryQuery

    //ex 15.37
    //if member is not Query query; but shared_ptr<Query_base> sp
    //no change for OrQuery, use BinaryQuery constructor to intialized the shared_ptr member

private:
};

#endif
