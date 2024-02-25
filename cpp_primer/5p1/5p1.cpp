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
    cout << endl << "==== Ex 5.3 ====" << endl;
    // rewrite while loop with comma operator instead of a block;
    int sum = 0, val = 1;
    while (val <= 10)
        sum += val, ++val; //use postfix ++ so that sum + 1 instad of 2
    cout << "Sum of 1 to 10 inclusive is " << sum << endl;

    int case_ctr = 1;
    /* switch (case_ctr) {
        // An variable is in scope start from current case and in scope for the following case, 
        // so it can only be decalared in first in scope case, then can be assigned in the following scoped case. 
        // If initialized in fisrt scope case, the case may be skipped and following case may need to use the initialized value, (error)
        // If want to both declare and initialize in only current scope, use {} enclose it
        case 1:
            string file_name; // error, file_name will have implicit initializer as empty string, so this statement contains both declaration and initialzation
            int ival; // ok, ival is not initialized
            // int jval;
            break;
        case 2:
            int jval = 0; // error, first case only can decalare, not initialized
        case 3:
            jval = 2;
    } */

    cout << ('a' + 'b') << endl; //97 + 98 = 195, 0x61 + 0x62
    cout << 'ab' << endl; //24930, 0x6162, two bytes together
    cout << ('a' << 8) + 'b' << endl; // first left shif 1 byte
    char a1[] = {'a', '\0'}; // equals char a1[] = "a"
    char b1[] = "b";
    cout << strcat(a1, b1) << endl; //ab

    cout << endl << "==== Ex 5.9 5.10 5.11 5.12 ====" << endl;

    /* test input string as follows:
            Apple is apple;
    It's not        banana;
            ff is ff; it's not fl, not      Ff;
    fl is not fi;
    
    */
    cout << "Input a series of string text as a sentence, hit ENTER twice when finished: " << endl;
    string s_line; // hold total input
    string line_runtime; // hold runtime input line
    while (getline(cin, line_runtime) && !line_runtime.empty()) {
        s_line += line_runtime;
        s_line += '\n'; // getline will not include newline, so output need to add newline
        // if (cin.get() == '\n') { // getline use Enter as finished, so if we want break input, hit ENTER again
        //     break;
        // } // this cin.get will chunk the first character in each line (except the first line, why?)
    }

    cout << "Original input is: " << endl << s_line << endl;

    cout << "Original input using iter method is: " << endl;
    
    for (auto iter = s_line.begin(); iter != s_line.end(); ++iter) {
        cout << *iter;
    }
    // s_line is now contains words, space, tabs, newlines
    auto iter = s_line.begin();
    int acnt = 0; // initial count of vowels in s_line to 0
    int cnt_blankspace = 0;
    int cnt_tabs = 0;
    int cnt_newlines = 0;

    int occur_ff = 0;
    int occur_fl = 0;
    int occur_fi = 0;
    while (iter != s_line.end()) {
        switch (*iter)
        {
        // contain lower or upper vowels a e i o u, aCnt + 1
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            ++acnt;
            break;
        // count number of blank spaces in s_line
        case ' ':
            ++cnt_blankspace;
            break;
        // count number of tabls in s_line
        case '\t':
            ++cnt_tabs;
            break;
        // count number if new_lines in s_line
        case '\n':
            ++cnt_newlines;
            break;
        default:
            break; // break this switch
        }

        // counts the number of occurrences of the following two-character sequences: ff, fl, and fi
        /*
        // we cannot use int + int since if a,b,c,d =  1,2,3,4, then a + d = 5, switch will also match b + c since 2 + 3 also 5
        switch (*iter + *(iter+1)) // this is char 1 byte int value + char 1 byte int value, byte to int first, then add two int
        {
        case ('f' + 'f'): //'ff' is two bytes concatenated together first, then transfer to int, should use 'f' + 'f'
            ++occur_ff;
            break;
        case ('f' + 'l'):
            ++occur_fl;
            break;
        case ('f' + 'i'):
            ++occur_fi;
            break;
        default:
            break; // break this switch
        }
        */
        switch (((*iter) << 8) + *(iter+1)) // this is char 1 byte left shif 1 byte, then + next char 1 byte int value, byte to int first, then add two int
        {
        case ('ff'): //'ff' is two bytes concatenated together first, then transfer to int, equals first f left shift 4bit (1byte) then add second f
            ++occur_ff;
            break;
        case ('fl'):
            ++occur_fl;
            break;
        case ('fi'):
            ++occur_fi;
            break;
        default:
            break; // break this switch
        }

        ++iter;
    }

    cout << "count of vowels in text: " << acnt << endl;
    cout << "count of blank spaces in text: " << cnt_blankspace << endl;
    cout << "count of tabs in text: " << cnt_tabs << endl;
    cout << "count of new lines in text: " << cnt_newlines << endl;
    cout << "count of 'ff' in text: " << occur_ff << endl;
    cout << "count of 'fl' in text: " << occur_fl << endl;
    cout << "count of 'fi' in text: " << occur_fi << endl;

    return 0;
}
