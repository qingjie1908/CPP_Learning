#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

// #include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


// "g++ -D NDEBUG -std=c++20 6p47.cpp -o 6p47_NDEBUG" to complie to a 6p47_NDEBUG not running the ndebug part
// "g++ -std=c++20 6p47.cpp -o 6p47_DEBUG" to complie to a 6p47_DEBUG will be running the ndebug part

void vecprint(const vector<string> &svec1, decltype(svec1.size()) i)
{
    if (i < svec1.size())
    {
        cout << svec1[i] << " ";
        #ifndef NDEBUG
        cout << __FILE__ << " : in function : " << __func__ << " at line : " << __LINE__ << " : " << endl
        << "Compiled on : " << __DATE__ << " " << __TIME__ << endl << "Vector size is : " << svec1.size() << endl;
        #endif
        vecprint(svec1, i+1);
    } else {
        return;
    }
}

int main()
{   
    vector<string> str1 = {"This", "is", "Qingjie!"};
    decltype(str1.size()) start_print_point = 1;
    cout << "Print start from the " << (start_print_point + 1) << "th element in the vector: " << endl;
    vecprint(str1, start_print_point);
    return 0;
}