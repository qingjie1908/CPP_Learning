#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

constexpr int a = 2+3;

int main()
{
    vector<int> ivec1(5, 1);
    auto cnt = ivec1.size();
    for (decltype(ivec1.size()) ix = 0; ix != ivec1.size(); ix++, cnt--){
        ivec1[ix] = cnt;
        cout << ivec1[ix] << " ";
    }
    cout << endl;
    

    cout << endl << "==== Ex 4.33 ====" << endl;
    int x = 5, y = 9;
    int z1 = (3 ? ++x, ++y : --x, --y);
    // first:  eval 3 ? ++x, ++y : --x; return ++x, ++y, return ++y (10)
    // second z = (10, --y), return z = --y, first y = 9, then z = y =9
    cout << x << " " << y << " " << z1 << endl; // 6, 9, 9

    x = 5; y = 9; // back to initial setting
    int z2 = (0 ? ++x, ++y : --x, --y);
    // first: 0 ? ++x, ++y : --x; return --x;
    // then z2 = (--x, --y); --x = 4, --y =8; z2 = --y = 8
    cout << x << " " << y << " " << z2 << endl; // 4, 8, 8

    x = 5; y = 9; // back to initial setting
    int z3 = (3 ? x++, y++ : x--, y--);
    // first:  eval 3 ? x++, y++ : x--; return x++, y++, then return y++ (x change to 6)
    // second z = (y++, y--), first y++ return 9, y change to 10
    // then y--, return 10, y change to 9, z = 10
    cout << x << " " << y << " " << z3 << endl; // 6, 9, 10

    x = 5; y = 9; // back to initial setting
    int z4 = (0 ? x++, y++ : x--, y--);
    // first, eval 0 ? x++, y++ : x--; return x--,
    // second (x--, y--), fist x-- return 5, x change to 4, then y-- retrun 9, y change to 8
    // z4 = y-- = 9
    cout << x << " " << y << " " << z4 << endl; // 4, 8, 9


    char cval; // 1 Byte
    cout << "size of type char in this machine: " << sizeof(char) << " Bytes." << endl;
    int ival; // 4 Bytes
    cout << "size of type int in this machine: " << sizeof(int) << " Bytes." << endl;
    unsigned int ui; // 4 Bytes
    cout << "size of type unsigned int in this machine: " << sizeof(unsigned int) << " Bytes." << endl;
    short int si; // 2 Bytes
    cout << "size of type short int in this machine: " << sizeof(short int) << " Bytes." << endl;
    unsigned short int usi; // 2 Bytes
    cout << "size of type unsigned short int in this machine: " << sizeof(unsigned short int) << " Bytes." << endl;
    long int li; // 8 Bytes
    cout << "size of type long int in this machine: " << sizeof(long int) << " Bytes." << endl;
    long long int lli; // 8 Bytes
    cout << "size of type long long int in this machine: " << sizeof(long long int) << " Bytes." << endl;
    float fval; // 4 Bytes
    cout << "size of type float in this machine: " << sizeof(float) << " Bytes." << endl;
    double dval; // 8 Bytes
    cout << "size of type double in this machine: " << sizeof(double) << " Bytes." << endl;
    long double ld; // 8 Bytes
    cout << "size of type long double in this machine: " << sizeof(long double) << " Bytes." << endl;

    
    cval = 'a' + 3; // chart prompt to int first, then add int 3, then converted to char for assignement (left covert to right)
    fval = ui - ival * 1.0; // ival convert to double, then ui to double, then substraction to signed float 
    ui = 3; fval = 1.1;
    ival = ui * fval; // float to unsigned int, then multiply to dval
    cout << ui * fval << " " << ival << endl; // 3.0

 

    int a[2] = {0, 1};
    int (&b)[2] = a;
    cout << b[0] + b[1] << endl;

    return 0;

}