template <typename T>
int compare(const T& obj1, const T& obj2){
    if (obj1 < obj2) return -1;
    if (obj2 < obj1) return 1;
    return 0;
}

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

int main(){
    int ret;
    Sales_data obj1("aa", 2, 3.0);
    Sales_data obj2("bb", 3, 1.2);

    ret = compare(obj1, obj2); 

    //Sales_data has no < operator, here the compiler just see the use of template compare,
    //just check if number of arguments is correct, or if they have the same type...
    //when compile, it will flag error

    //but, if Slaes_data has conversion operator, operator double() const { return revenue;}
    //when obj1 < obj2, it will use this conversion operator to convert obj1 and obj2 to obj1.revenue and obj2.revenue then compare two double !!!

    switch (ret)
    {
    case 1:
        std::cout << "obj1 > obj2" << std::endl;
        break;

    case -1:
        std::cout << "obj1 < obj2" << std::endl;
        break;

    case 0:
        std::cout << "obj1 = obj2" << std::endl;
        break;
    
    default:
        break;
    }

    return 0;
}