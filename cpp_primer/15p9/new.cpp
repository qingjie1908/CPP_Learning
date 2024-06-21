#include <string>
#include <iostream>
#include <memory>
class Query;

class WordQuery{
friend class Query;

private:
    WordQuery(const std::string& s):word(s){}

    std::string word;

};

class Query{

public:
    Query(const std::string& s):sp_qb(std::make_shared<WordQuery>(s)){
        std::cout << "Query(string)" << std::endl;
    } 
private:
    std::shared_ptr<WordQuery> sp_qb;
};

int main(){
    Query q("hello");
}