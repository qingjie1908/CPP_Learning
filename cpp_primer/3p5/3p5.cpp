#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// constexpr int a = 2 + 3;
int main()
{
    constexpr size_t array_size = 10;
    // int array_size = 10;
    int ia[array_size];
    for (size_t ix = 0; ix <= array_size - 1; ++ix) {
        ia[ix] = ix;
        cout << ia[ix] << endl;
    }

    cout << endl << "==== Ex3.35 ====" << endl;

    int arr1[10] = {};
    // pbeg point to the first arr1 element, 
    // pend point to one past the last element in arr1
    int *pbeg = arr1, *pend = arr1 + 10;
    // p to hold runtime pointer
    int *p = pbeg;
    cout << "Input a series of integer, max 10 int, to creat a array: " << endl;
    int i1; // i1 to hold runtime input int
    while (cin >> i1 && p < pend) {
        *p = i1;
        ++p;

        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "The array of size 10 are: " << endl;
    for (int *p1 = arr1; p1 < pend; ++p1) { // p1 cannot dereference the last end nonexit element
        cout << *p1 << " ";
    }
    cout << endl;

    cout << "set all the elements in arr1 to 0, output are: " << endl;
    for (int *p1 = arr1; p1 < pend; ++p1) {
        *p1 = 0;
        cout << *p1 << " ";
    }
    cout << endl;

    cout << endl << "==== Ex3.36 ====" << endl;

    constexpr size_t arrsize = 5;
    int arr2[arrsize] = {};
    int *pa2 = arr2;
    int arr3[arrsize] = {};
    int *pa3 = arr3;
    vector<int> vec1(10,0);
    vector<int> vec2(10,0);

    if (arr2 == arr3) {
        cout << "arr2 = arr3" << endl;
    } else if (arr2 < arr3) {
        cout << "arr2 < arr3" << endl;
    } else if (arr2 > arr3) {
        cout << "arr2 > arr3" << endl;
    }

    if (vec1 == vec2) {
        cout << "vec1 = vec2" << endl;
    } else if (vec1 < vec2) {
        cout << "vec1 < vec2" << endl;
    } else if (vec1 > vec2) {
        cout << "vec1 > vec2" << endl;
    }

    return 0;
}
