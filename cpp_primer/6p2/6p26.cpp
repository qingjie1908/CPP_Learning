#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    cout << argc << " arguments have been passed into main function." << endl;
    cout << "print the values of the arguments passed to main: " << endl;
    // following way is ok, use argc to count how many values need to be printed
    // for (int i = 0; i < argc; ++i)
    // {
    //     cout << *argv << endl;
    //     ++argv;
    // }

    for(; *argv != nullptr; ++argv)
    {
        cout << *argv << endl;
    }

    return 0;
}