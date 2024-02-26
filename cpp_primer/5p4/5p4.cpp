#include <iostream>
#include <string>
#include <vector>
#include <array>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::array;

int main()
{
    string s1, s2;
    cout << "==== Ex 5.19 ====" << endl;
    do {
        cout << "Please enter two string: " << endl;
        cin >> s1 >> s2;
        int status_compare;
        (s1 < s2) ? status_compare = -1 : (s1 == s2) ? status_compare = 0 : status_compare = 1;
        switch (status_compare)
        {
            case -1:
            cout << "s1: " << s1 << " < " << "s2: " << s2 << endl;
            break;
            case 0:
            cout << "s1: " << s1 << " = " << "s2: " << s2 << endl;
            break;
            case 1:
            cout << "s1: " << s1 << " > " << "s2: " << s2 << endl;
            break;
        
            default:
            break;
        }
    } while (cin); // always trun until hit ctrl + D

    return 0;

}