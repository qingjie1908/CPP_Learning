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
    const char ca1[] = "A string example"; //16, null terminator added automatically
    const char ca2[] = "A different string"; //18, null terminator added automatically

    // In this case, ca is an array of char but is not null terminated. 
    // The result is unde- fined. The most likely effect of this call is that 
    // strlen will keep looking through the memory that follows ca 
    // until it encounters a null character.
    const char ca3[] = {'h','e','l','l','o'}; //8
    const char ca4[] = {'1'}; //9

    const char ca5[] = {'h','e','l','l','o', '\0'}; //5
    const char ca6[] = {'1', '\0'}; //1
    const char *p = ca1;
    // strlen(ca1);
    cout << "ca1 length is: " << strlen(ca1) << endl;
    cout << "ca2 length is: " << strlen(ca2) << endl;
    cout << "ca3 length is: " << strlen(ca3) << endl;
    cout << "ca4 length is: " << strlen(ca4) << endl;
    cout << "ca5 length is: " << strlen(ca5) << endl;
    cout << "ca6 length is: " << strlen(ca6) << endl;

    const char *cp3 = ca3;
    while (*cp3) {
        cout << "Output each char in ca3 which does not have null terminator \\0: " << endl;
        cout << *cp3 << endl;
        ++cp3;
    }

    const char *cp5 = ca5;
    while (*cp5) {
        cout << "Output each char in ca5 which have null terminator \\0: " << endl;
        cout << *cp5 << endl;
        ++cp5;
    }

    cout << endl << "==== Ex 3.39 ====" << endl;

    //compare char ca1 and ca2
    cout << "Compare char string ca1[] and ca2[]: " << endl;
    if (strcmp(ca1, ca2) == 0) {
        cout << "char string ca1 = ca2" << endl;
    } else if (strcmp(ca1, ca2) < 0) {
        cout << "char string ca1 < ca2" << endl;
    } else if (strcmp(ca1, ca2) > 0) {
        cout << "char string ca1 > ca2" << endl;
    }

    cout << "Compare string s1 and s2: " << endl;
    string s1(10, 'a');
    string s2(10, 'a');
    if (s1 == s2) {
        cout << "s1 = s2" << endl;
    } else {
        cout << "s1 != s2" << endl;
    }

    cout << endl << "==== Ex 3.40 ====" << endl;
    string s3; // hold total input
    string s4; // hold run time input string

    cout << "Input a series of string/words, hit ENTER when finished: " << endl;
    while (cin >> s4) {
        s3 += s4;
        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Output string s3: \n" << s3 << endl;
    cout << "Output each character in s3: " << endl;
    for (auto s : s3) {
        cout << s << " ";
    }
    cout << endl;

    auto size_s3 = s3.size();

    cout << "size of s3 is: " << size_s3 << endl;

    cout << endl <<  "Put first half s3 into char array carr1: " << endl;
    // auto it_mid = (s3.end() - s3.begin())/2; // right operand is int not iterater
    auto it_mid = s3.begin() + (s3.end() - s3.begin())/2;

    string s3_firsthalf;
    for (auto it = s3.begin(); it != it_mid; ++it) {
        s3_firsthalf += (*it);
    }

    char carr1[100]; // size large enough to hold char
    carr1[99] = '\0'; // add null terminator for c style char
    
    for (int i = 0; i < s3_firsthalf.size(); ++i) {
        carr1[i] = s3_firsthalf[i];
    }

    cout << endl << "Output first half input as char array carr1: " << endl;

    for (char *p = carr1, *pend = carr1 + s3_firsthalf.size(); p != pend; ++p) {
        cout << *p;
    }
    cout << endl;

    cout << endl << "Output total char array carr1: " << endl;
    char *pcarr1 = carr1;
    while (*pcarr1) {
        cout << *pcarr1;
        ++pcarr1;
    }
    cout << endl;

    // ============================================

    cout << endl << "Put second half s3 into char array carr1: " << endl;
    string s3_secondhalf;
    for (auto it = it_mid; it != s3.end(); ++it) {
        s3_secondhalf += (*it);
    }

    char carr2[100];
    carr2[99] = '\0';

    for (int i = 0; i < s3_secondhalf.size(); ++i) {
        carr2[i] = s3_secondhalf[i];
    }

    cout << endl << "Output second half input as char array carr2: " << endl;
    for (char *p = carr2, *pend = carr2 + s3_secondhalf.size(); p != pend; ++p) {
        cout << *p;
    }
    cout << endl;

    cout << endl << "Output total char array carr2: " << endl;
    char *pcarr2 = carr2;
    while (*pcarr2) {
        cout << *pcarr2;
        ++pcarr2;
    }
    cout << endl;
    // ============================================

    char carr3[200];
    strcpy(carr3, carr1);
    strcat(carr3, carr2);

    cout << endl << "Output total char array carr3 add by carr1 and 2: " << endl;
    char *pcarr3 = carr3;
    while (*pcarr3) {
        cout << *pcarr3;
        ++ pcarr3;
    }
    cout << endl;


    return 0;
}