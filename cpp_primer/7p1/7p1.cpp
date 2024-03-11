#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main()
{
    Sales_data total; // object total to hold accumulated data;
    Sales_data trans; // object trans to hold each time read in data;
    if (read(cin, total)) // read first transaction
    {
        while(read(cin, trans)) // read remaining transaction
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(cout, total); // print total transaction in one kind isbn book
                total = trans; // initialize total to the different ISBN trans
            }
        }
        // after cin ends; the last trans has not been print yet
        print(cout, total);
    }
    else
    {
        std::cerr << "No data?!" << endl;
    }
    return 0;
}