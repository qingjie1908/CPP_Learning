#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main()
{
    cout << endl << "==== Ex 4.21 ====" << endl;

    vector<int> ivec1;

    cout << "Input a series of integer, hit ENTER when finished: " << endl;
    int i1; // hold runtime input int
    while (cin >> i1) {
        ivec1.push_back(i1);
        if (cin.get() == '\n'){
            break;
        }
    }

    cout << "Output the original ivec1: " << endl;
    for (auto iter = ivec1.begin(); iter != ivec1.end(); ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

    cout << "Output the odd value in ivec1: " << endl;
    for (decltype(ivec1.size()) i = 0; i != ivec1.size(); ++i) {
        !(ivec1[i]%2) ? (cout << "") : (cout << "The ivec[" << i << "]: " << ivec1[i] << " is odd value." << endl);
        !(ivec1[i]%2) ? ivec1[i] = ivec1[i] : ivec1[i] *= 2;
    }

    cout << "Output new ivec1 with each odd element doubled: " << endl;
    for (auto i : ivec1) {
        cout << i << " ";
    }
    cout << endl;

    cout << endl << "==== Ex 4.23 ====" << endl;
    string s = "world";
    string pl = s + s[s.size() - 1] == "s" ? "" : "s"; // size(), then +, then ==, then ?:, then =, output s
    cout << pl << endl; // s
    string pl2 = s + ((s[s.size() - 1] == 's') ? "" : "s");
    cout << pl2 << endl; //worlds
}