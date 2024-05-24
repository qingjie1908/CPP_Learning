#include <string>
#include <iostream>
#include <memory>

void read_and_store(std::istream& is, char* p_total)
{
    //char* p_total = new char[20]; //hold 20 char

    //read string word from input
    std::string read_word;
    while(std::cin >> read_word){
        const char* read_p = read_word.c_str(); //return pointer to the first element of the null terminated char array
        for(size_t i = 0; i < strlen(read_p); ++i){ //strlen does not count the null terminator
            *p_total = read_p[i];
            ++p_total; //p_total point to next pos in char[20]
        }
        //after read a word into char[20] finish
        //add a tab
        *p_total = ' ';
        ++p_total;
        //note there is exception that p_total out of range char[20]
    }

}

int main()
{
    char* p_total = new char[20];

    read_and_store(std::cin, p_total);

    std::cout << p_total << std::endl;
    std::cout << *p_total << std::endl;
    std::cout << strlen(p_total) << std::endl;

    delete [] p_total;
    //input : new total larger larger larger
    //output:
    //new total larger larger larger
    //n
    //31

}