#ifndef QUERY
#define QUERY

#include <string>
#include <memory>

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/Query_base.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/WordQuery.h"

class TextQuery;
class QueryReuslt;

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


    QueryResult eval(const TextQuery& t ) const {return p_qb->eval(t);} //call virtual eval() in Query_base, dynamic binding, default inline
    std::string rep() const {std::cout << "Query::rep()" << std::endl; return p_qb->rep();} //call virtual rep() in Query_base, dynamic binding, define inside class, default inline

    //for copy construct we cannot use new Query_base(*(orig.p_qb) since Query_base is abstract class, cannot create object of its type
    //so use pure virtual Query_base* clone() in Query_base; 
    //implement clone() in derived class, retrun Derived_class*; use that Derived_class* to new()

    Query(const Query& orig){
        p_qb = orig.p_qb->clone();
    }

    Query& operator=(const Query& rhs){
        if(this != &rhs){
            delete p_qb; //free this orig part
            p_qb = rhs.p_qb->clone();
        }
        return *this;
    }

    Query(Query&& orig){
        p_qb = orig.p_qb; //move version clone
        //update orig
        orig.p_qb = nullptr;
    }

    Query& operator=(Query&& orig){
        if(this != &orig){
            delete p_qb; //free this orig part
            p_qb = orig.p_qb; //steal orig pointed heap memory
            orig.p_qb = nullptr; //update orig so that it is safe to be delete
        }
        return *this;
    }

    ~Query(){
        std::cout << "~Query()" << std::endl;
        delete p_qb;
    }

private:
    //constructor to take std::shared_ptr<Query_base> cause operator return pointer to And/Or/NorQuery object
    //we make it private cause we will not use Query_base and derived class to constrcut Query in user code
    //Query_base and derived class are implementation class for Query; so that's why we need to friend operator overloaed function, they need to access private constrcutor
    Query(Query_base* p_p):p_qb(p_p){std::cout << "Query(p)" << std::endl;} // default inline
    Query_base* p_qb; //point to heap memory
};

inline
std::ostream& operator<<(std::ostream& os, const Query& q){return os << q.rep();}

//public constructor of Query::
inline
Query::Query(const std::string &s): p_qb(new WordQuery(s)) {std::cout << "Query(string)." << std::endl;}

//point 1: inline tells the compiler that the function code can be expanded where the function is called, instead of effectively being called.
//point 2: important!!! note for a class method, if it's marked as inline It tells the compiler that the function definition can be repeated.
//point 3: class method define inside class are default inline
//point 4: if class method define outside of class like here, it should explicit inline
//if we define constructor in seperate Query.cpp file, then if we in another cpp file construct Querry but only include Query.h; then it cannot find the defination of the constructor


#endif