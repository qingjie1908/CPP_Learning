#include <iostream>
#include <fstream>
#include <string>

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27_TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27_QueryResult.h"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile); //store the file and build query map

    while(true){
        std::cout << "enter word to look for, or q to quit: " << std::endl;
        std::string s;
        if(!(std::cin >> s) || s == "q") break;
        QueryResult obj2 = tq.query(s);
        //after query(), shared ptr in query() destroyed, but shared_ptr in obj2 exist
        print(std::cout, obj2) << std::endl;
    }
    //after while loop, shared ptr in obj2 destroyed, memory freed;

    //TexQuery has no data member of type shared_ptr, its only be created when call member func query()

}


int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27.txt");

    runQueries(input_file);

    input_file.close();

    //
    /*
    enter word to look for, or q to quit: 
    qingjie
    element occurs 7 times: 
            (line 1) this is qingjie
            (line 3) this qingjie! is;
            (line 4) "qingjie is here!
            (line 5) !qingjie;
            (line 6)     "qingjie" with a tab.
            (line 7)     qingjie is qingjie!

    enter word to look for, or q to quit: 
    is
    element occurs 5 times: 
            (line 1) this is qingjie
            (line 2) this is apple;
            (line 3) this qingjie! is;
            (line 4) "qingjie is here!
            (line 7)     qingjie is qingjie!

    enter word to look for, or q to quit: 
    banana
    not find this element.

    enter word to look for, or q to quit: 
    q
    */

}