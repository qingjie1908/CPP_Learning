#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <initializer_list>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

void vecprint(const vector<string> &svec1, decltype(svec1.size()) i)
{
    if (i < svec1.size())
    {
        cout << svec1[i] << " ";
        vecprint(svec1, i+1);
    } else {
        ;
    }
}

int factorial(int val)
{
    if (val != 0)
    {
        return factorial(val - 1) * val;
    }
    return 1;
}

int main()
{
    cout << factorial(4) << endl;
    
    vector<string> str1 = {"This", "is", "Qingjie!"};
    decltype(str1.size()) start_print_point = 1;
    cout << "Print start from the " << (start_print_point + 1) << "th element in the vector: " << endl;
    vecprint(str1, start_print_point);
    return 0;
}