#include <fstream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"

// void process_string(std::string& read_line){
//     std::string operator_symbol = "~|&";
//     std::vector<std::string> operand_vec;
//     for(auto pos = read_line.find_first_of(operator_symbol); pos != std::string::npos;){
//         std::string operand_s = 
//     }
// }



// //ex 15.42 (b), can access history Query
// void runQueries(std::ifstream &infile)
// {

//     std::cout << "Process Query by Line or by Sentence? enter 1 for by line, 2 for by sentence: " << std::endl;
//     int check_type;
//     while (std::cin >> check_type){
//         if(check_type != 1 || check_type != 2){
//             std::cout << "invalid input, please enter 1 (by line) or 2 (by sentence)." << std::endl;
//         } else {
//             break;
//         }
//     }

//     TextQuery tq(infile, check_type); //store the file and build query map by line or by sentence

//     while(true){
//         std::cout << "enter word to look for, or q to quit: " << std::endl;
//         std::string read_line;
//         if(!(std::getline(std::cin, read_line) || read_line == "q")) break;
//         void process_string(read_line);
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
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p9.txt");

    TextQuery text(input_file);

    Query q = Query("fiery") & Query("bird") | Query("wind");

    QueryResult q_r = q.eval(text);

    std::cout << "Executing Query for: " << q << std::endl;
    
    print(std::cout, q_r);

    //ex 15.42 (c), only print results in limit line range
    print(std::cout, q_r, 2, 4);
    /*
    element occurs 3 times: 
	(line 2) Her Daddy says when the wind blows
	(line 4) like a fiery bird in flight.
    */

    //ex 15.40, no match, just putput ff | bb
    Query q1 = Query("ff") | Query("bb");
    QueryResult q1_r = q1.eval(text);
    std::cout << "Executing Query for: " << q1 << std::endl;
    print(std::cout, q1_r);

    input_file.close();

    //ex 15.42 (a), organized input file sentence by sentence, not line by line
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p9.txt");
    TextQuery text2(input_file, 2);
    Query q2("fiery");
    QueryResult q2_r = q2.eval(text2);
    std::cout << "Executing Query for: " << q2 << std::endl;
    print(std::cout, q2_r);

    input_file.close();

    //output
    /*
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

    return 0;
}