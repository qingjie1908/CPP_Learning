#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class PrintString{
public:
    PrintString(std::istream& is_p = std::cin):is(is_p){}
    void operator()(){//operator () take zero paramenter
        std::string read_line;
        while(std::getline(is, read_line)){ //if ifstream, it will not print last newline, will print newline before the last newline
            std::cout << read_line << std::endl;
            if(&is == &std::cin){
                vec_s.push_back(read_line);
            }
        }
        if(is.fail()){
            std::cout << "is.fail() is true" << std::endl; //hit eof is also consider fail()
        }
    }

    void print_vec(){
        for(auto item : vec_s){
            std::cout << item << std::endl;
        }
    }
private:
    std::istream& is;
    std::vector<std::string> vec_s;
};

int main()
{

    std::ifstream if1;
    if1.open("/Users/qingjie/github/CPP_Learning/cpp_primer/14p8/14p35.txt");
    PrintString obj1(if1);
    obj1();
    if1.close();
    obj1.print_vec();

    PrintString obj2(std::cin);
    obj2();
    obj2.print_vec();

    return 0;
}