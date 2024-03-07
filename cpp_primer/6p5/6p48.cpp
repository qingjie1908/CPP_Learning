#include <iostream>
#include <string>
#include <vector>
// #include <initializer_list>

#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<string> str1 = {"This", "is", "Qingjie!"};
    string s = "END";
    string sought = "END";
    while (cin >> s && s != sought) {}
    assert(cin); // cin will always be true, assert(cin) will do nothing ??
    /*
    assert(s != "END")
    after input END in terminal, it will display as follows
    ae
    ae
    end
    END
    Assertion failed: (s != "END"), function main, file 6p48.cpp, line 20.
    zsh: abort      ./6p48
    */
    // assert(s != "END");
    // cout << " s is not END" << endl;   
    return 0;
}