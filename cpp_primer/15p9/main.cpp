#include <fstream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
// #include "15p9/Query_base.h"
// #include "15p9/WordQuery.h"
// #include "15p9/NotQuery.h"
// #include "15p9/BinaryQuery.h"
// #include "15p9/AndQuery.h"
// #include "15p9/OrQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"



// void runQueries(std::ifstream &infile)
// {
//     TextQuery tq(infile); //store the file and build query map

//     while(true){
//         std::cout << "enter word to look for, or q to quit: " << std::endl;
//         std::string s;
//         if(!(std::cin >> s) || s == "q") break;
//         QueryResult obj2 = tq.query(s);
//         //after query(), shared ptr in query() destroyed, but shared_ptr in obj2 exist
//         print(std::cout, obj2) << std::endl;
//     }
//     //after while loop, shared ptr in obj2 destroyed, memory freed;

//     //TexQuery has no data member of type shared_ptr, its only be created when call member func query()

// }

int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27.txt");

    TextQuery text(input_file);

    Query q = Query("fiery") & Query("bird") | Query("wind");

    QueryResult q_r = q.eval(text);

    std::cout << "Executing Query for: " << q << std::endl;
    
    print(std::cout, q_r);

    input_file.close();

    std::shared_ptr<std::string> p(std::make_shared<std::string> ("hello"));
    p = std::make_shared<std::string> ("hello");



}