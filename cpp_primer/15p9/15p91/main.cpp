#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p91/Query.h"

int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p9.txt");

    TextQuery text(input_file);

    Query q1("fiery");
    QueryResult q1_r = q1.eval(text);
    std::cout << "Executing Query for: " << q1 << std::endl;
    print(std::cout, q1_r);

    Query q = Query("fiery") & Query("bird") | Query("wind");

    QueryResult q_r = q.eval(text);

    std::cout << "Executing Query for: " << q << std::endl;
    
    print(std::cout, q_r);

    input_file.close();

    return 0;
    //output
    /*
    WordQuery(string).
    Query(string).
    Executing Query for: Query::rep()
    Wordquery::rep()
    fiery
    element occurs 2 times: 
            (line 4) like a fiery bird in flight.
            (line 5) A beautiful fiery bird, he tells her,
    WordQuery(string).
    Query(string).
    WordQuery(string).
    Query(string).
    BinaryQuery::construct.
    AndQuery::constrcut
    Query(sp)
    WordQuery(string).
    Query(string).
    BinaryQuery::construct.
    OrQuery::construct.
    Query(sp)
    Executing Query for: Query::rep()
    BinaryQuery::rep()
    Query::rep()
    BinaryQuery::rep()
    Query::rep()
    Wordquery::rep()
    Query::rep()
    Wordquery::rep()
    Query::rep()
    Wordquery::rep()
    fiery & bird | wind
    element occurs 3 times: 
            (line 2) Her Daddy says when the wind blows
            (line 4) like a fiery bird in flight.
            (line 5) A beautiful fiery bird, he tells her,
    */
}