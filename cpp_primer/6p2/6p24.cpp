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
using std::begin; // for built in array
using std::end; // for built in array

void swap(int* &a, int* &b)
{
    int *inter = a; //intermediate pointer to hold pointer a address a
    a = b;
    b = inter;
}

void print(int i, int *jbeg, int *jend)
{
    cout << "Print int i: " << i << endl;
    cout << "Pirnt element in int array j: " << endl;
    while (jbeg != jend) {
        cout << *jbeg << " ";
        ++jbeg;
    }
    cout << endl;
}

void print2(const int (&ia)[2])
{
    for(size_t i = 0; i != 2; ++i){
        cout << ia[i] << " ";
    }
    cout << endl;
}

int main()
{
    cout << "==== Ex 6.22 ====" << endl;
    int a = 3, b = 4;
    int *ap = &a;
    int *bp = &b;
    swap(ap, bp);
    cout << a << " " << b << endl;
    cout << *ap << " " << *bp << endl;

    cout << endl << "==== Ex 6.23 ====" << endl;
    int i = 0, j[2] = {0, 1};
    print(i, begin(j), end(j));
    

    cout << endl << "==== Ex 6.23 ====" << endl;

    print2(j);

    char p1[5][6] = {"prog", "-d", "-o", "ofile", "data0"};
    cout << p1[1] << endl;

    char *p2[] = {"prog", "-d", "-o", "ofile", "data0"};
    cout << *p2[3] << endl;

    return 0;
}