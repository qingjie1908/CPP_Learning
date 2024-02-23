#include <iostream>
#include <string>
#include <vector>
// #include <iterator>

using std::cin;
using std::cout;
using std::endl;

using std::string;

using std::vector;
using std::begin;
using std::end;

constexpr int a = 2 + 3;

int main()
{
    int iarr1[] = {1, 2, 3, 4, 5};
    // using std::begin;
    // int *pbeg = begin(iarr1);
    // using std::end;
    // int *pend = end(iarr1);
    vector<int> ivec1(begin(iarr1), end(iarr1));
    cout << "Thel" << endl;

    cout << endl << "==== Ex 3.43 ====" << endl;

    int ia[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    int ib[3] = {1, 2, 3};
    for (int i : ib) {
        cout << i << endl;
    }

    cout << "using range for and direct type to read: " << endl;
    for (int *p : ia) {
        cout << *p << " ";
        cout << *(p + 1) << " ";
        cout << *(p + 2) << " ";
        cout << *(p + 3) << " ";
    }
    cout << endl;

    cout << "using range for and auto type to read: " << endl;
    for (auto &p : ia) { //must use referecne in outer loop for multi dimension array
        for (auto q : p) {
            cout << q << " ";
        }
    }
    cout << endl;
    

    cout << "using subscript and direct type to read: " << endl;
    for (int (*p)[4] = ia; p != end(ia); ++p) {
        for (int i = 0; i < 4; ++i) {
            cout << (*p)[i] << " ";
        }
    }
    cout << endl;

    cout << "using subscript and auto type to read: " << endl;
    for (int (*p)[4] = ia; p != end(ia); ++p) {
        for (int i = 0; i < 4; ++i) {
            cout << (*p)[i] << " ";
        }
    }
    cout << endl;

    // cout << "using pointer to read: " << endl;
    // for (int (*p)[4] = ia; p != end(ia); ++p) {
    //     for (int *q = *p; q != end(*p); ++q) {
    //         cout << *q << " ";
    //     }
    // }
    // cout << endl;
}