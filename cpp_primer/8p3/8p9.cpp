#include <iostream>
#include <string>
#include <sstream>

std::istream& read_and_write(std::istream& s)
{
    auto init_state = s.rdstate();
    std::cout << "stream S initial state value s.rdstate() is: " << init_state << std::endl;
    std::cout << "stream S initial badbit s.badbit value is: " << s.badbit << std::endl;
    std::cout << "stream S initial failbit s.failbit value is: " << s.failbit << std::endl;
    std::cout << "stream S initial eofbit s.eofbit value is: " << s.eofbit << std::endl;
    std::cout << "stream S initial goodbit s.goodbit value is: " << s.goodbit << std::endl;

    std::string input_real_val;
    std::string input_total_val;
    while (!s.eof())
    {
        s >> input_real_val;
        std::cout << "Last input: " << input_real_val << std::endl;
    }

    // after hit end of life
    auto end_state = s.rdstate();
    std::cout << "stream S end state value s.rdstate() is: " << end_state << std::endl;
    std::cout << "stream S end badbit s.badbit value is: " << s.badbit << std::endl;
    std::cout << "stream S end failbit s.failbit value is: " << s.failbit << std::endl;
    std::cout << "stream S end eofbit s.eofbit value is: " << s.eofbit << std::endl;
    std::cout << "stream S end goodbit s.goodbit value is: " << s.goodbit << std::endl;

    // reset stream S
    s.clear();
    std::cout << "stream S reset state value s.rdstate() is: " << s.rdstate() << std::endl;
    std::cout << "stream S reset badbit s.badbit value is: " << s.badbit << std::endl;
    std::cout << "stream S reset failbit s.failbit value is: " << s.failbit << std::endl;
    std::cout << "stream S reset eofbit s.eofbit value is: " << s.eofbit << std::endl;
    std::cout << "stream S reset goodbit s.goodbit value is: " << s.goodbit << std::endl;

    return s;
}

int main()
{

    //print the contents of an istringstream object
    std::cout << std::endl << "=== enter some contents then hit ctrl-D ===" << std::endl;
    std::istringstream istr_stream;
    std::string line = "a";
    while(getline(std::cin, line))
    {
        istr_stream.str(line); // copy string "line" to istr_stream
        read_and_write(istr_stream);
    }

    //after ctrl-D hit
    std::cout << "cin now state is " << std::cin.rdstate() << std::cin.badbit << std::cin.failbit << std::cin.eofbit << std::cin.goodbit << std::endl; 

    std::cin.clear();

    std::cout << "cin after clear state is " << std::cin.rdstate() << std::cin.badbit << std::cin.failbit << std::cin.eofbit << std::cin.goodbit << std::endl; 

    return 0; 
}