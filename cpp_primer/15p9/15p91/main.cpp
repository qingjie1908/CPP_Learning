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

}