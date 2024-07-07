#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"
#include <unordered_set>


int main()
{
    Sales_data obj1("aa", 5, 3.0);
    Sales_data obj2("aa", 5, 3.0);
    Sales_data obj3("bb", 5, 3.0);

    std::unordered_multiset<Sales_data> s1;
    s1.insert(obj3);
    s1.insert(obj2);
    s1.insert(obj1);

    for(auto item : s1){
        std::cout << item << std::endl;
    }
    /*
    aa 5 15 3
    aa 5 15 3
    bb 5 15 3
    */

    return 0;

}