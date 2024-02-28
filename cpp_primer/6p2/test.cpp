#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;
using std::runtime_error;
using std::invalid_argument;

int main()
{
    string s1 = "Hello";
    vector<int> ivec = {1, 2, 3};
    for (auto &r : s1) {
        r = tolower(r);
    }
    // cout << s1 << endl;
    // for (auto &r : s1) {
    //     r = toupper(r);
    // }
    cout << s1 << endl;
    for (auto &r : ivec) {
        ++r;
    }
    cout << s1 << endl;
    return 0;
}