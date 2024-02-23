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
    cout << endl << "======== Ex 3.17 ========" << endl;
    vector<string> svec1; // store total input string
    string s1; // store runtime input
    cout << "Input a series of string, hit ENTER when finished: " << endl;
    while (cin >> s1) {
        svec1.push_back(s1);
        if (cin.get() == '\n') { // Hit ENTER for input finished
            break;
        }
    }

    // change each word to uppercase
    // *it is each string/word in the svec1, 
    for (auto it = svec1.begin(); svec1.begin() != svec1.end() && it != svec1.end(); ++it) {
        for (auto it1 = it->begin(); it->begin() != it->end() && it1 != it->end(); ++it1) {
            // it->begin() equals (*it).begin, *it is string element in svec1
            *it1 = toupper(*it1); //*it1 is a single char in each string element
        }
    }

    cout << endl << "Output are: " << endl;
    //print the upper case output, eight words to a line
    for (decltype(svec1.size()) i = 0; i < svec1.size(); ++i) {
        cout << svec1[i] << " ";
        //eight words in a line
        if (i/8 != (i + 1)/8) {
            cout << endl;
        }
    }

    // In case last line does not have 8 words, print additional newline
    cout << endl;

    cout << endl << "======== Ex 3.19/3.21 ========" << endl;
    vector<int> ivec1; // Hold total input
    int i1; //hold runtime input

    cout << "Input a series of integer, Hit Enter when finished: " << endl;

    while (cin >> i1) {
        ivec1.push_back(i1);
        if (cin.get() == '\n') {
            break;
        }
    }

    //print the sum of each pair adjacent elements
    cout << "Print the sum of each pair adjacent elements: " << endl;
    for (auto it = ivec1.begin(); ivec1.begin() != ivec1.end() && it != (ivec1.end() - 1); ++it) {
        // condition it < ivec1.end() - 1 because we need dereference (it+1)
        cout << *it + *(it + 1) << " ";
    }

    cout << endl;

    // print the sum of the first and last elements, 
    // followed by the sym of the seconde and second-to-last, and so on
    cout << "Print the sum of fist and last, then second fist and second last... :" << endl;
    auto it_end = ivec1.end() - 1; //end iterator, one past the end of ivec1, -1 to index last element
    for (auto it = ivec1.begin(); ivec1.begin() != ivec1.end() && it != ivec1.end(); ++it) {
        if (it <= it_end) {
            cout << *it + *it_end << " ";
            --it_end;
        } 
        else {
            break; // when it > it_end; end calculation
        }
    }
    cout << endl;

    cout << endl << "======== Ex 3.23 ========" << endl;

    cout << "Input a series of 10 integer, hit ENTER when finished: " << endl;
    vector<int> ivec2; // ivec2 to hold all input
    int i2; // i2 to hold runtime input

    while (cin >> i2) {
        ivec2.push_back(i2);
        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Print twice the vector's value: " << endl;

    for (auto it = ivec2.begin(); it != ivec2.end(); ++it) {
        *it = 2 * (*(it));
        cout << *it << " ";
    }

    cout << endl;

    return 0;
}

