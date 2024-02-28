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

vector<int>::iterator change_val(int, vector<int>::iterator);
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int); 
vector<int> vec(10);
int a = count("abcda", 'c');
double c = sum(vec.begin(), vec.end(), 3.8);

bool hascap(const string &s, int &occur, decltype(s.size()) &index_first) // top level const, can pass const and nonconst argument to &s
{
    bool hascap = false; // initialize hascap to false
    index_first = s.size(); // record first occurrence of capitial letter
    for(decltype(s.size()) i = 0; i != s.size(); ++i) {
        if (isupper(s[i])) {
            if (index_first == s.size()) { // true if first occurent not happen yet
                index_first = i; // record first occur index
            }
            ++occur;
            hascap = true;
        } 
    }
    return hascap;
}

void lowstring(string &s)
{
    for(auto &c : s) {
        c = tolower(c);
    }
}

int main()
{
    cout << "==== Ex 6.17 ====" << endl;
    cout << "Input a string, hit ENTER when finished: " << endl;
    string s1;
    while (cin >> s1) { // only last single string stored in s1
        if (cin.get() == '\n') {
            break;
        }
    }

    int occur = 0;
    decltype(s1.size()) index_first = 0;

    if (hascap(s1, occur, index_first)) {
        cout << "Input string has " << occur 
        << " capital letters, the first captial is the " 
        << index_first << " in string s1: " << s1[index_first] << endl;
    } else {
        cout << "Input string has no capital letters." << endl;
    }

    cout << "Change input string into all lowercase: " << endl;
    lowstring(s1);
    cout << s1 << endl;
    return 0;

}