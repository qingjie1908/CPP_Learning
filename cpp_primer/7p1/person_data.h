#ifndef BASIC_H
#define BASIC_H
#include <string>
#include <vector>
#endif

#ifndef PERSON_DATA
#define PERSON_DATA
struct Person{
    std::string name;
    std::string address;
    std::vector<std::string> vec1 = {name, address};
    std::string get_name() const {return name;} // not need to change name, so use const to indicate *this.get_name() is read only 
    std::string get_addr() const {return address;} // get func only read object member
};
#endif