#include <memory>
#include <string>

int main()
{
    std::unique_ptr<double> p1; //p1 is now a null ptr
    std::unique_ptr<int> p2(new int(42)); //p2 point to memory has int 42

    //1. unique ptr cannot support ordinary copy or assign
    std::unique_ptr<std::string> p3(new std::string("Stegosaurus"));

    //std::unique_ptr<std::string> p4(p3); //error, no copy for unique_ptr
    //call to implicitly-deleted copy constructor of 'std::unique_ptr<std::string>' (aka 'unique_ptr<basic_string<char>>')


    std::unique_ptr<std::string> p5;
    //p5 = p3; //error: no assign for unique_ptr
    //object of type 'std::unique_ptr<std::string>' (aka 'unique_ptr<basic_string<char>>') cannot be assigned because its copy assignment operator is implicitly deleted
}