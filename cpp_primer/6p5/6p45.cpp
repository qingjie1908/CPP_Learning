#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::string;

inline bool isshorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

constexpr string isshorter1(const string &s1, string &s2)
{
    return s2;
}

int main()
{
    string s1 = "asdfg";
    string s2;
    cin >> s2;
    string s3;
    s3 = isshorter1("sfd", s2);
    cout << isshorter("hello", "hellp") << endl;
    cout << isshorter1("hellp", s2) << endl;
    cout << s3 << endl;
    return 0;
}