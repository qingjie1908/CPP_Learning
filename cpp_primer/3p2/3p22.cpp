#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    const string hexdigits = "0123456789ABCDEF";
    cout << "Enter a series of numbers between 0 and 15" << " seperated by spaces. "
         << "Hit ENTER when finished: " << endl;
    string result; // will hold the resulting hexify'd string
    string::size_type n; // hold numbers from the input
    // while (cin >> n && cin.get() != '\n') { // input string follwed directly by ENTER will not be counted in
    while (cin >> n) {
        if (n < hexdigits.size()) {
            result += hexdigits[n];
            result += " ";
        }

        if (cin.get() == '\n') {
            break;
        }
    }
    cout << "Your hex number is: " << result << endl;

    cout << "\n" << "=============" << endl;

    // change all the characters in a string to X
    string str2 = "Happy Day24!";
    for (char &c : str2) {
        c = toupper(c);
    }
    cout << "the upper case of string 2 is: " << str2 << endl;

    string str3(10, 'c');
    decltype(str3.size()) i = 0; // i to indicate the index of str3 and initialized as 0, first char of s2
    while (i < str3.size()) {
        str3[i] = toupper(str3[i]);
        ++i;
    }
    cout << str3 << endl;

    cout << "\n" << "=============" << endl;

    string s4; // to hold the total string from input
    string s5; // to hold the current string from input
    cout << "write a string/line/lines with punctuation, hit enter twice when finished: " << endl;

    while (getline(cin, s5) && !s5.empty()) { // getline func will use enter as default end of life
        s4 += s5; // read line does not include newline even when use newline to indicate end of line
        s4 += '\n'; // add new line for each read line
    }

    // enter ctrl + D to end the input for s4
    cout << "Input string/line/lines are: " << '\n' << s4 << endl;

    // find out punctuation and remove it
    char emptychar; // '' is a constant char and connot be assigned to variable,
    for (auto &c : s4) {
        if (ispunct(c)) {
            c = emptychar; // '' is a constant char and connot be assigned to variable char c
        }
    }

    cout << "Output string/line/lines without punctuation: \n" << s4 << endl;

    return 0;
}