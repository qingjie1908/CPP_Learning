#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

int main()
{
    std::stringstream s_str;
    std::fstream s_file;
    std::string write_line;
    
    std::string new_file_path = std::filesystem::current_path();
    new_file_path.append("/file_8p10.txt");

    std::cout << "file_8p10 created, pelease write some lines to it." << std::endl;
    s_file.open(new_file_path, std::fstream::app);
    
    while(getline(std::cin, write_line)) {
        s_file << write_line << std::endl;
    }
    //now s_file is in output mode, close first then read it

    s_file.close();


    std::vector<std::string> s_vec1;
    std::string read_line;
    s_file.open(new_file_path); // open the created txt file
    while(getline(s_file, read_line)) { //now s_file is in input mode
        s_vec1.push_back(read_line);
    }

    s_file.close();


    std::cout << "each line in file is: " << std::endl;
    for(size_t i = 0; i != s_vec1.size(); ++i){
        std::cout << "s_vec1[" << i << "] = " << s_vec1[i] << std::endl;
    }

    std::cout << "read each word in vec: " << std::endl;
    for(auto iter : s_vec1){
        //std::stringstream s_str;
        s_str.str(iter); // copy each line in s_vec1 and store in stringstream
        std::string read_word;
        //now use stringstream to read each word in the line to read_word
        while (s_str >> read_word) {
            std::cout << read_word << std::endl;
        }

        // if s_str is defined outside for loop, then it will not be destroyed the next iteration
        // on the end of fist iteration, s_str finishes input a line and end-of-file is signaled and the next input operation on the seconde iteration will fail
        // so we need to clear status first then iter the next element in s_vec1
        // if s_str is defined inside this loop, then we don't need to clear since it will be destroyed each iteration
        s_str.clear();
    }

    return 0; 
}