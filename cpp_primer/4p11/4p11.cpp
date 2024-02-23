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
    const char *pc = "ab";
    const char a1[2] = {'a', '\0'};
    cout << *pc << endl;
    cout << pc << endl;

    const char pc2 = 'a';

    const int a = 10;
    const int *ip = &a;
    cout << *ip << endl;
    cout << ip << endl;

    int a3[3] = {1, 2, 3};
    int *ip2 = a3;

    // using a const_cast in order to write to a const object is undefined
    // char *p = const_cast<char*>(pc); // can be compiled, 
    //  *p = 'b'; // error

    const char *cp;
    // const_cast only cast away low level const, 
    // so the type in a const_cast must be a pointer, reference, or pointer to member to an object type
    // const_cast<string>(cp); // error

    int b = 11;
    int *ip3 = &b;
    char *pc1 = reinterpret_cast<char *>(ip3);
    string str(pc1); // no compling error, but runtime error
    // actual object addressed by pc is an int, not a character. 
    // Any use of pc that assumes it’s an ordinary character pointer is likely to fail at run time.
    // or result in bizarre run-time behavior
    cout << str << endl;

    cout << endl << "==== Ex 4.36 ====" << endl;
    int i = 2;
    double d = 3.3;
    i *= static_cast<int>(d);
    cout << i << endl; //6

    cout << endl << "==== Ex 4.37 ====" << endl;
    int i1;
    double d1;
    const string *ps;
    char *pc3;
    void *pv;

    // old style
    pv = (void*)ps;
    cout << "pv type: " << typeid(pv).name() << endl;
    cout << "ps type: " << typeid(ps).name() << endl;
    // named cast ???
    // pv = const_cast<void*>(ps); //error

    // old style
    i1 = int(*pc3);
    cout << "i1 type: " << typeid(i1).name() << endl;
    cout << "pc type: " << typeid(pc3).name() << endl;
    // named cast
    // i1 = static_cast<int>(*pc);

    // old style
    pv = &d;
    cout << "pv type: " << typeid(pv).name() << endl;
    cout << "d type: " << typeid(d).name() << endl;
    // named cast
    // pv = static_cast<void*>(d);

    return 0;
}