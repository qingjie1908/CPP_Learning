#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main(int argc, const char *argv[])
{
    char *a1[] = {"prog", "-d", "-o", "ofile"};
    char a11[4][6] = {"prog", "-d", "-o", "ofile"};
    auto a22 = a11; // a22 has type char (*)[6], a pointer point to a char[6] ("prog")
    // a1 is an array of char *; not a pointer to a char[];
    // a1[0] is first char *, point to "prog", so *a1[0] is p; a1[0] is prog
    char **a33 = a1; // a3 is pointer (*), point to a1 first element, which is a1[0], a pointer to cstyle string, so its a ponter point to a char *
    cout << "*a1 is: " << *a1 << endl; //prog
    cout << "*(a1+1) is: " << *(a1+1) << endl; //-d
    cout << "*a1[0] is: " << *a1[0] << endl; //p
    cout << "(*a1)[0] is: " << (*a1)[0] << endl; //p
    cout << "a1[0] is: " << a1[0] << endl; //prog
    cout << "a11[0][0] is: " << a11[0][0] << endl; //p
    cout << "a11[0] is: " << a11[0] << endl; //prog

    
    // char (*a2)[] = {"prog", "-d", "-o", "ofile"}; error
    // a2 is a pointer to a char[]; so too may initializer, should only have one "cstyle string"
    // const char (*a2)[] = "prog"; // error, "prog" is const char [5], change to const char *; cannot be used to initialize const char (*)[]
    
    char a4[] = "prog";
    char *a3 = a4; // correct; *a3 is p
    cout << "*a3 is: " << *a3 << endl; //p
    cout << "a3 is: " << a3 << endl; //prog
    cout << "a4 is: " << a4 << endl;

    for (auto a5 = "prog"; a5 != std::end("prog"); ++a5)
    {
        cout << *a5 << " ";
    }
    cout << endl;

    cout << "Main function takes two const char and concatenate them." << endl;

    constexpr int enough_large_size = 10000;

    char string_result[10000] = ""; // initialize to null

    // argv[0] is the name of the program, first parameter we want to use is argv[1]

    strcpy(string_result, argv[1]); // add cosnt char *(argv+1)
    strcat(string_result, *(argv + 2)); // concatenate const char *(argv+2)

    cout << "concatenated arguments char a[] and char b[] in main function arugument are: " << endl
    << string_result << endl;


    return 0; // string_result is a char[], whihc is a char *
}

