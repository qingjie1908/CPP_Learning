#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

void printcarray()
{

}

int main()
{
    // practice for pointer to array
    char c1 = 'a';
    char c2[] = "abc"; // use "" initializer will add terminator '\0' to char array automatically
    cout << "size of c2: " << std::end(c2) - std::begin(c2) << endl; //4

    char c3[] = {'a', 'b', 'c', '\0'};
    cout << "size of c3: " << std::end(c3) - std::begin(c3) << endl; //4

    // compare cstype char string c2 and c3, 0 for equal, positive value if c2 > c3; negative value if c2 < c3;
    int c_style_compare = strcmp(c2, c3);
    cout << "Compare ctype string c2 and c3 is : " << c_style_compare << endl;

    // size of c stype char string array: 
    cout << "size of c stype char string array: " << std::size(c2) << endl; //4

    size_t size_c2 = std::size(c2);
    for (auto i = std::begin(c2); i != std::end(c2); ++i) 
    {
        cout << *i << " ";
    }
    cout << endl;
    
    for (size_t i = 0; i < std::size(c3); ++i)
    {
        cout << c3[i] << " ";
    }
    cout << endl;

    // const char [4] "abc" as initializer, transfer to pointer point to first element if "abc"
    const char *c4 = "abc";
    // char *c5 = {'a', 'b', 'c', '\0'}; error
    // char *c5 = c2; // ok, *c5 is a
    char *c5 = c3;
    cout << *c4 << endl; // a
    cout << *(c4+1) << endl; //b
    cout << *(c5 + 1) << endl; //b


    // second size must be defined, should be larger than the largest ctype string element, including null
    char c6[][7] = {"abc", "efg", "hjkl", "asfret"};
    cout << c6[0] << endl; // abc (not including null)
    cout << strlen(c6[0]) << endl; //3 (not couting null)
    cout << std::size(c6[0]) << endl; // 7 (size() counts null)

    for (size_t i = 0; i != std::size(c6[0]); ++i)
    {
        cout << c6[0][i] << " "; // a b c null null null null
    }
    cout << endl;
 

    // when initializer c6 is a arrary
    // it transfer to a pointer to point its first element
    // which is a pointer point to "abc"
    // "abc" is a char array of 7 (including terminator)
    // so initilized lvalue variable is char (*c8)[]
    // char c6[][7] = {"abc", "efg", "hjkl", "asfret"};
    char (*c8)[7] = c6; // c8 is a pointer point to a char[7], which is "abc", without (), then c8 point to array of char*, quals to char (*c8)[7] = &c6[0];
    cout << "*c8 is: " << *c8 << endl; //"abc"
    cout << "*(c8+1) is: " << *(c8+1) << endl; // if we want to use c8 + 1, defind c8 must use complete type, which is char (*c8)[7] = c6;, cannot use char (*c8)[] = c6;
    char *c9 = *c8; // *c8 is array "abc", will be converted a pointer to char 'a'
    cout << "*c9 is : " << *c9 << endl; // a

    // define a pointer c88 to pointer c8
    // first rvalue is some kind of &, &c8, define **c88 = &c8
    // *c8 is array[7] of char, char [7]; **c88 -> c8
    auto **c88 = &c8; // **c88 is *(*c88) is *(c8) is "abc" (char[7]); equals {char (**c88)[7] = &c8;}
    cout << "*c88 is: " << *c88 << endl; //*c88 is pointer c8, pointer c8's value (point to array "abc"), hold the address of "abc", 0x16fdff0a0
    cout << "c8 is: " << c8 << endl; //pointer c8, 0x16fdff0a0
    cout << "c9 is address of 'a' : " << c9 << endl; //  abc ???
    cout << "address of 'a': " << &((*c8)[0]) << endl; // abc ???
    cout << "&c8 is: " << &c8 << endl; // address of pointer c8, 0x16fdff050
    cout << "**c88 is: " << **c88 << endl; // *c8, which is "abc"
    cout << "c88 is: " << c88 << endl; // pointer c88, its value is the address of pointer c8, 0x16fdff050

    



    
    auto c10 = c6; // c10 is char (*c10)[7]
    cout << "*c10 is: " << *c10 << endl; // abc
    cout << "*(c10 + 1) is: " << *(c10 + 1) << endl; // efg

    int a = 10;
    int *ap = &a;
    cout << "*ap is: " << *ap << endl; // 10
    cout << "ap is: " << ap << endl; // address of int a
    int **app = &ap;
    cout << "*app is: " << *app << endl; // pointer ap, value of ap, address of int a
    cout << "&ap is: " << &ap << endl;
    cout << "app is: " << app << endl; //hold the address of pointer ap
    cout << "**app is: " << **app  << endl; // int a 10

    char **c11 = &(c9); // c11 is same as c10, c11 point to first element of c6
    cout << *c11 << endl; // abc

    char c12 = 'e';
    cout << "char c12 is: " << c12 << endl;
    char *c12p = &c12;
    cout << "&c12 is: " << &c12 << endl; // address of c12
    cout << "c12p is: " << c12p << endl; //hold the address of char c12

    cout << "*c12p is: " << *c12p << endl; // 'e'

    
}
