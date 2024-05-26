#include <string>
#include <iostream>

class Employee{
public:
    //default constructor
    Employee(){++unique_num; unique_id = "ID" + std::to_string(unique_num);}

    Employee(std::string name_para):name(name_para){++unique_num; unique_id = "ID" + std::to_string(unique_num);}

    //default copy_constructor will copy unique_id, without increment unique_num, not wanted
    Employee(const Employee& origi){++unique_num; name = origi.name; unique_id = "ID" + std::to_string(unique_num);}

    //default copy assignement operator = will copy unique_id, so rewirte a new val it into lhs operand ; not wanted
    Employee& operator=(const Employee& rhs){name = rhs.name; return *this;} //= not touch unqiue_id

private:
    static int unique_num;
    std::string name;
    std::string unique_id;

};
//not add static again, since we already has declartion
int Employee::unique_num = 0;

int main()
{
    Employee obj1("AA");
    Employee obj2 = obj1; //use own defind copy_constructor, not systhesized one

    //now obj1 and obj2 has same name but different unique_id

    Employee obj3; //obj3 has empty name, but different unique_id as obj1 and obj2

    obj3 = obj2; //use own defined copy_assignment operator, not touch unqiue id, only assign name

}