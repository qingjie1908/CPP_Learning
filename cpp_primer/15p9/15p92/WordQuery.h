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

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/Query_base.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p92/QueryResult.h"
class Query;
class QueryResult;

class WordQuery : public Query_base {
friend class Query; //since eval and rep are private, need to made friend, cause Query::sp_qb->eval() need
//also, Query need WordQuery constrctor
public:
    
protected:
    //inherite default virtual constructor from Query_base
    ~WordQuery(){
        std::cout << "~WordQuery()" << std::endl;
    }

    WordQuery(const WordQuery& orig){
        query_word = orig.query_word;
    }

    WordQuery& operator=(const WordQuery& rhs){
        query_word = rhs.query_word;
        return *this;
    }

    WordQuery(WordQuery&& orig){
        query_word = std::move(orig.query_word);
    }

    WordQuery& operator=(WordQuery&& rhs){
        if(this != &rhs){
            query_word = std::move(rhs.query_word);
        }
        return *this;
    }

private:
    WordQuery(const std::string& sp):query_word(sp){std::cout << "WordQuery(string)." << std::endl;}

    QueryResult eval(const TextQuery& t) const override {return t.query(query_word);}
    std::string rep() const override {std::cout << "Wordquery::rep()" << std::endl; return query_word;}

    std::string query_word;

    WordQuery* clone() const & override {return new WordQuery(*this);}
    WordQuery* clone() && override {return new WordQuery(std::move(*this));}

};


#endif