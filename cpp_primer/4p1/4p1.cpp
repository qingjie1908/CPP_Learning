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
    int *p;
    int a = 10;
    decltype(*p) b = a;
    decltype(&p) c;
    decltype(&a) d1;

    cout << 30 / 3 * 21 % 5 << " " << (((30 / 3) * 21) % 5) << endl;
    cout << -30 / 3 * 21 % 4 << " " << -2 << endl;

    int num1;
    cout << "Enter a number: " << endl;
    while (cin >> num1) {
        if (cin.get() == '\n') {
            break;
        }
    }

    if (num1 % 2) {
        // equal 1, trun
        cout << "Input number is odd." << endl;
    } else {
        // equal 0, false
        cout << "Input number is even." << endl;
    }

    const char *cp = "Hello World!";
    if (cp && *cp) {
        cout << "True" << endl;
    }

    int i; double d;
    d = i = 3.5;
    cout << d << " " << i << endl;

    i = d = 3.5;
    cout << d << " " << i << endl;

 

    int *ip = 0;

    vector<string> svec1 = {"This", "is", "Qingjie"};
    auto iter = svec1.begin();

    cout << "*iter++ : " << *iter++ << endl; //This
    // error : cout << "(*iter)++ : " << (*iter)++ << endl; no string ++
    // error : cout << "*iter.empty() : " << *iter.empty() << endl; // iter has no member empty
    cout << "iter->empty() : " << iter->empty() << endl; // "False"
    cout << "*iter : " << *iter << endl; // is
    // error: cout << "++*iter : " << ++*iter << endl; // no ++ string
    cout << "iter++->size() : " << iter++->size() << endl; // 2
    cout << "iter->size(): " << iter->size() << endl; //7

   return 0;
}