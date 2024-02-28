#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "Chapter6.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main()
{
    int x; // store run time input
    int result; // store factorial result of x
    cout << "Input a integer x, hit ENTER when finished: " << endl;
    while (cin >> x) // x will only take the last cin
    {
        if (cin.get() == '\n')
        {
            break;
        }
    }

    try
    {
        if (x <= 0)
        {
            throw std::invalid_argument("Input integer should be larger than zero!!!");
        }
        result = fact(x);
        cout << "Output factorial value of input x is: " << result << endl;
    }
    catch(const std::invalid_argument& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Please enter unsigned int x agian: " << endl;
        cin >> x;
        result = fact(x);
        cout << "Output factorial value of input x is: " << result << endl;
    }
    return 0;
}

