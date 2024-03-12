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
    Person():name("Qingjie"),address("Library"){} // own version defalut constructor
    // if use Person() = default; name and address will be empty string 
};
std::istream &read_person(std::istream &is, Person &pers)
{
    is >> pers.name >> pers.address;
}
std::ostream &print_person(std::ostream &os, const Person &pers)
{
    os << pers.get_name() << pers.get_addr();
}
#endif