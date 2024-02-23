#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<int> v1;

int main()
{
    vector<int> ivec1;
    int a; // hold input int

    cout << "Input a series of int, hit ENTER when finished: " << endl;
    while (cin >> a) {
        ivec1.push_back(a);

        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Output of the input int: " << endl;
    for (int n : ivec1) {
        cout << n << endl;
    }

    cout << '\n' << "================" << '\n' << endl;

    vector<string> svec1;
    string b; // hold input string

    cout << "Input a series of string, hit ENTER when finished: " << endl;
    while (cin >> b) {
        svec1.push_back(b);

        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Output of the input string: " << endl;
    for (string n : svec1) {
        cout << n << endl;
    }

    cout << '\n' << "================" << '\n' << endl;


    return 0;
}