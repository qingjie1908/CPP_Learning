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
    unsigned char bits = 0223; // char has 8 ints, 0233 is octal literal
    cout << "bits represent char: " << bits << endl;

    bool status;
    // unsigned char a1 = 0b00010010;
    unsigned char a1 = 0b00010010;
    unsigned char a2 = 0b00000010;
    status = a1 & a2;
    cout << "status is: " << status << endl;

    cout << "a1 represents: " << a1 << endl;

    cout << endl << "==== Ex 4.25, 4.26 ====" << endl;
    unsigned char q1 = 0b01110001;
    unsigned long int q2 = 0b01110001; // 8 Bytes
    unsigned int q3 = 0b01110001; // 4 Bytes
    long int q4 = 0b01110001; //signed 8 Bytes
    int q5 = 0b01110001; //signed 8 Bytes
    cout << "char q1 is: " << q1 << endl;
    cout << "size of char q1 is: " << sizeof(q1) << " Bytes" << endl;
    cout << "size of ulong int q2 is: " << sizeof(q2) << " Bytes" << endl;
    cout << "size of unsigned int q3 is: " << sizeof(q3) << " Bytes" << endl;
    cout << "size of signed long int q4 is: " << sizeof(q4) << " Bytes" << endl;
    cout << "size of signed int q5 is: " << sizeof(q5) << " Bytes" << endl;

    cout << "UL int q2 is: " << q2 << endl;

    // ~q1 << 6; // will not change q1, q1 still represent char 'q';
    // since char is small integer, it will be prompted to larger integral type UL
    // ~q1 will result 32 bit (4 bytes for int), then shift left 6, most significant 1, indicate negative value
    cout << "char ~q1 << 6 is: " << (~q1 << 6) << endl;
    // q2 is a ULONG, ~q2 << 6 positive 64 bit int
    cout << "ulong int ~q2 << 6 is: " << (~q2 << 6) << endl;
    // q3 is unsighned int 4 Bytes, ~q3 << 6 postive 32 bit int
    cout << "unsigned int ~q3 << 6 is: " << (~q3 << 6) << endl;
    // q4 is signed long, ~q4 << 6 negative 64 bit int
    cout << "signed long int ~q4 << 6 is: " << (~q4 << 6) << endl;
    // q5 is signed int, ~q5 << 6 negative 32 bit int
    cout << "signed int ~q5 << 6 is: " << (~q5 << 6) << endl;

    cout << endl << "==== Ex 4.27 ====" << endl;
    unsigned long ul1 = 3; //0x00000003
    unsigned long ul2 = 7; //0x00000007

    cout << "ul1 & ul2 is: " << (ul1 & ul2) << endl; //0x00000003
    cout << "ul1 | ul2 is: " << (ul1 | ul2) << endl; //0x00000007
    cout << "ul1 && ul2 is: " << (ul1 && ul2) << endl; //ture 1
    cout << "ul1 || ul2 is: " << (ul1 || ul2) << endl; //true 1

    cout << endl << "==== Ex 4.28 ====" << endl;
    cout << "size of string type: " << sizeof(std::string) << endl;
    string s1 = "This is Qingjie!";
    cout << "size of initialized string S1: " << sizeof(s1) << endl;
    vector<int> ivec1 = {1, 2, 3};
    vector<int> ivec2 = {1, 2};
    vector<string> svec1 = {"this", "is", "Qingjie"};
    vector<string> svec2 = {"this", "is"};
    cout << "size of initialized int vector ivec1: " << sizeof(ivec1) << endl;
    cout << "size of initialized int vector ivec2: " << sizeof(ivec2) << endl;
    cout << "size of initialized string vector svec1: " << sizeof(svec1) << endl;
    cout << "size of initialized string vector svec2: " << sizeof(svec2) << endl;
    cout << "size of unnitialized vector<int>: " << sizeof(vector<int>) << endl;
    cout << "size of unnitialized vector<string>: " << sizeof(vector<string>) << endl;
    cout << "size of int: " << sizeof(int) << endl;
    cout << "size of long int: " << sizeof(long int) << endl;
    cout << "size of char: " << sizeof(char) << endl;
    cout << "size of double: " << sizeof(double) << endl;
    cout << "size of long double: " << sizeof(long double) << endl;
    cout << "size of long long int: " << sizeof(long long int) << endl;
    cout << "size of bool: " << sizeof (2 < 3) << endl;
    int *p_int;
    string *p_string;
    double *p_double;
    char *p_char;
    vector<int> *p_vec_int;
    vector<string> *p_vec_string;
    cout << "size of *p_int and p_int " << sizeof(*p_int) << " " << sizeof(p_int) << endl;
    cout << "size of *p_string and p_string " << sizeof(*p_string) << " " << sizeof(p_string) << endl;
    cout << "size of *p_double and p_double " << sizeof(*p_double) << " " << sizeof(p_double) << endl;
    cout << "size of *p_char and p_char " << sizeof(*p_char) << " " << sizeof(p_char) << endl;    
    cout << "size of *p_vec_int and p_vec_int " << sizeof(*p_vec_int) << " " << sizeof(p_vec_int) << endl;
    cout << "size of *p_vec_int and p_vec_string " << sizeof(*p_vec_string) << " " << sizeof(p_vec_string) << endl;

    cout << endl << "==== Ex 4.28 ====" << endl;
    int x[10];
    int *p = x;
    cout << sizeof(x) << " " << sizeof(*x) << " " << sizeof(x)/sizeof(*x) << endl;
    cout << sizeof(p) << " " << sizeof(*p) << " " << sizeof(p)/sizeof(*p) << endl;

}