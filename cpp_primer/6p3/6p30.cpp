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

// bool str_subrange(const string &str1, const string &str2)
// {
//     if (str1.size() == str2.size())
//     {
//         return str1 ==  str2;
//     }
//     auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();

//     for (decltype(size) i = 0; i != size; ++i)
//     {
//         if (str1[i] != str2[i])
//         {
//             return; // error #1: no return value; compiler should detect this error
//         }
//     }
//     // error #2: control might flow off the end of the function without a return
//     // the compiler might not detect this error    
// }

int &get(int *array, int index)
{
    return array[index];
}

int main() 
{
    int ia[10];
    for (int i = 0; i != 10; ++i)
    {
        get(ia, i) = i;
    }
    
    cout << "Output ia: " << endl;
    for (int i = 0; i!=10; ++i)
    {
        cout << ia[i] << " " << endl;
    }
    cout << endl;
}