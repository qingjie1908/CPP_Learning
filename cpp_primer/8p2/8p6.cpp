#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

int main(int argc, char *argv[])
{
    // run command in terminal "./8p6 transaction_input.txt transaction_summary.txt"
    std::cout << "The program name is: " << argv[0] << std::endl; // which is './8p6' by default if we did not specify

    std::fstream input_transaction; // creat a file stream;
    input_transaction.open(argv[1]); // pass the file name through argument to main
    std::fstream output_transaction_summary; // create a file stream;
    output_transaction_summary.open(argv[2], std::fstream::app); // open file argv[2] in append mode, and write summary in it, it file not exist, it will create this file

    //input transaction file should have below format, string bookNo, unsigned int units_sold, double price
    /*
    0-321-71411-3 2 60.3
    0-321-71411-1 3 47.2
    ...
    */

    // ifread stream line by line
    /*
    std::string read_line; // hold the string line in transaction file
    if (input_transaction) { // check file argv[1] open successfully
        while(getline(input_transaction, read_line)) {

        }
    }
    */

    // if want to read stream word by word
    /*
    if (input_transaction) { // check file argv[1] open successfully
        std::string word; // read word by word from input_transaction file
        while (input_transaction >> word) { // delimiter is tab/newline/space
            if(std::ispunct(word.back())) { // word.back return last char in string
                word.erase(word.end()-1); // word.end() return past-last iterator, here erase ','
            }
        }
    }
    */

    Sales_data total; // variable to hold the running sum;
    Sales_data trans; // varaiable to hold the current transaction
    if(input_transaction && output_transaction_summary){ // check file argv[1] open successfully, argv[2] created and open susccessfully
        if (read(input_transaction, total)){ //read(), input_transaction stream will read word by word from file argv[1]
            // and read the first transaction into total
            while (read(input_transaction, trans)){ // read the remaining transaction
                if (total.isbn() == trans.isbn()){
                    total.combine(trans);
                } else {
                    // print to terminal console first
                    print(std::cout, total);
                    std::cout << std::endl; // no endl in member func print()
                    // print summary to file argv[2]
                    print(output_transaction_summary, total);
                    output_transaction_summary << std::endl;
                    // update new total with different bookNo
                    total = trans;
                }
            }
            print(std::cout, total) << std::endl; // print the last transaction
            std::cout << std::endl;
            // print last transaction into file argv[2]
            print(output_transaction_summary, total);
            output_transaction_summary << std::endl;
        } else {
            std::cerr << "No data?!" << std::endl;
        }
    } else {
        std::cerr << "input or output file has not opened successfully" << std::endl;
    }

    input_transaction.close();
    output_transaction_summary.close();
}
