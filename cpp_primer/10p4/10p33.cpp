#include <iostream>
#include <vector>
#include <string>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/1p5/Sales_item.h"
#include <numeric> //for accumulate
#include <fstream> //include filesystem


int main(int argc, char* argv[4])
{
    // run command: ./10p33 input_10p33.txt output_10p33.txt output_2_10p33.txt
    std::string curr_dir = std::filesystem::current_path();
    curr_dir += "/";

    std::string input_file_path = curr_dir + argv[1]; //input_10p33.txt
    std::string output_file_path1 = curr_dir + argv[2];
    std::string output_file_path2 = curr_dir + argv[3];

    std::ifstream f_i(input_file_path);
    std::istream_iterator<int> is_iter(f_i);
    std::istream_iterator<int> is_iter_eof;

    std::ofstream f_o1(output_file_path1, std::ofstream::app); //create file if no exist before
    std::ofstream f_o2(output_file_path2, std::ofstream::app);

    std::ostream_iterator<int> os_iter1(f_o1, " ");
    std::ostream_iterator<int> os_iter2(f_o2, "\n");


    while(is_iter != is_iter_eof){
        if(*is_iter%2){ //*iter, read from istream
            os_iter1 = *is_iter;
        } else {
            os_iter2 = *is_iter;
        }
        ++is_iter;
    }
    





    

}