#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    // when argv[] defined, argc will be calculated auto matically
    // for example, this cpp is compiled into '8p4' running below command in terminal
    // ./8p4 file_input.txt file_output.txt
    // argv[0] = "8p4", which is the program name
    // argv[1] = "file_input.txt"
    // argv[2] = "file_output.txt"
    // argc = 3, the elements number in char*[]

    std::ifstream input(argv[1]); // same as input(*(argv+1))
    std::vector<std::string> read_input;
    std::string read_line;

    if (input){ // check input file is ok
        while(getline(input, read_line)){
            read_input.push_back(read_line);
        }
    }

    input.close(); // after read finished, close ifstream
    
    std::cout << "Contents in input_file are: " << std::endl;
    for(auto iter = read_input.begin(); iter != read_input.end(); ++iter){
        std::cout << *iter << std::endl; // getline not include newline
    }

    std::cout << "write contents in input_file_txt to output_file_txt. " << std::endl;
    std::ofstream output(*(argv + 2)); // same as output(argv[2])
    if (output){
        for (auto iter : read_input){
            output << iter << std::endl;
        }
    }
    output.close();

    // read from input file then write to output_file_2.txt
    std::cout << "read from input_file then wirte to output_file_2.txt. " << std::endl;
    input.open(argv[1]);
    output.open(argv[3]);
    if (input){
        if (output){
            while(getline(input, read_line)){
                output << read_line << std::endl; // getline not include newline
            }
        }
    }
    output.close();
    input.close();

    // read from input file char by char
    input.open(argv[1]); // must close then open again, otherwise the begin point will be the end of input file
    output.open(argv[4]); // if nofile exist, it will create this file
    if(output){
        while(!input.eof()){ //while(input.get()) will read eof all the time and never stop
            output << char(input.get()); // input.get() return int
        }
    }

    input.close();
    output.close();

    return 0;
    // Run below command
    // ./8p4 file_input.txt file_output.txt file_output_2.txt file_output_3.txt

}
