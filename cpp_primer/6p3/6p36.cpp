#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::string;
using std::vector;

using std::cout;
using std::cin;
using std::endl;

int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};
decltype(odd) *arrPtr(int i)
{
    return (i % 2) ? &odd : &even;
}

// function return reference to array
int (&funr(int a))[5] {
    return (a % 2) ? odd : even;
}

// same as previous funr
auto funrr(int a) -> int (&)[5]
{
    return (a % 2) ? odd : even;
}

std::string str1[10] = {"This", "is", "an", "array", "of", "ten", "strings", "stringname", "is", "str1"};

// using type alias, function returns a reference to an array of ten strings
using strarr10 = string[10];
strarr10 &func1(int a) //  need &, funtion return array is not allowed
{
    return str1;
}

// using decltype
decltype(str1) &func2(int a) // need &, funtion return array is not allowed
{
    return str1;
}

// using trailing return
auto funca(int a) -> string (&)[10] { return str1; }
// string (&funca)[10] = str1;

// direct type
string (&func5(int a)) [10]
{
    return str1;
}

auto func4(int a) -> int {
    return 4;
}
int main()
{
    int *arrPtr1 = odd; // same as int *arrPtr = &odd[0]
    // int *arrPtr1 = &odd; // error, &odd is a value of type int (*)[5], not a point to int only

    int (*arrPtr2)[5] = arrPtr(11);
    int ele = (*arrPtr2)[4]; // 5
    cout << "ele is : " << ele << endl;
    cout << "arrPtr2 is: " << arrPtr2 << endl; // first address of array odd, 0x100a98000
    cout << "arrPtr(11) is: " << arrPtr(11) << endl; // first address of array odd, 0x100a98000
    cout << "&odd is: " << &odd << endl; // 0x100a98000
    cout << "&odd[0] is: " << &odd[0] << endl; // 0x100a98000
    cout << "&odd[1] is: " << &odd[1] << endl; // 0x100a98004 (add 4 bytes)
    

    cout << "*arrPtr(11) is: " << *arrPtr(11) << endl; // 0x100a98000
    cout << "*arrPtr(11)[2] is: " << *arrPtr(11)[2] << endl; // undefined ?? 1936287828
    cout << "(*arrPtr(11))[2] is: " << (*arrPtr(11))[2] << endl; //5

    // 1. int (*arrPtr)[5] = &odd; declare and define arrPtr is a pointer to array of ten ints, value is address of odd array &odd, not address of first odd array element &odd[0]
    // 2. int (*arrPtr2)[5] = arrPtr(11), which is arrPtr2 = arrPtr = &odd 
    // 2. dereference arrPtr,  *arrPtr is array {1, 3, 5, 7, 9}

    cout << str1[0] << endl; // This
    string (&str_1)[] = str1; // need to add (), otherwise str_1 is array of ten &, error, no array of reference
    str_1[0] = "Thisss";
    cout << str1[0] << endl; // Thisss

    string (&str11)[10] = func1(3);
    str11[0] = "This4s";
    cout << str1[0] << endl; // This4s

    strarr10 &str12 = func1(3); // using type alias strarr
    str12[0] = "This5s";
    cout << str1[0] << endl; // This5s 
    // 1. strarr& func1 = str1, func1 is a reference of array of ten strings
    // 2. define str11 as a reference to array of ten 10 strings, and str11 = func1
    // str12 is just same as str11, both reference to array of ten 10 strings, which is str1

    strarr10 &str21 = func2(4);
    str21[0] = "This6s";
    cout << str1[0] << endl;

    string (&str22)[] = func2(5);
    str22[0] = "This7s";
    cout << str1[0] << endl;

    string (&str5)[] = func5(77);
    str5[0] = "This8s";
    cout << str1[0] << endl;

    funr(5)[0] = 11; // funr(5): int (&funr)[5] = odd, funr(5)[0] is is odd[0] 
    cout << odd[0] << endl; // 11

    funrr(6)[0] = 10; // funrr(6): int (&funrr)[5] = even; funrr[0] is even[0]
    cout << even[0] << endl; // 10

    return 0;
}