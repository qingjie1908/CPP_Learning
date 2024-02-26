#include <iostream>
#include <string>
#include <vector>
// #include <exception>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main()
{
    cout << "==== Ex 5.20 ====" << endl;
    string s_runtime; // hold runtime input
    vector<string> svec; // hold total input string
    cout << "Input a series of string, ctrl + D to finish or same word occurs twice in sccession will stop input process: " << endl;
    while (cin >> s_runtime) {
        if (!svec.empty() && (*(svec.end() - 1) == s_runtime)) {
            cout << "\'" << s_runtime << "\'" << " occurs twice in sccession." << endl;
            break;
        } else {
            svec.push_back(s_runtime);
            cout << "no word was repeated successively yet." << endl;

        }    
    }
    

    cout << endl << "===== Ex 5.24 ====" << endl;
    cout << "Input two integer i1, i2 then divide i1/i2: " << endl;

    int i1, i2;
    cin >> i1 >> i2;

    if (i2 == 0) {
        throw std::runtime_error("second int i2 should not be zero");
    }

    cout << "i1/i2 is: " << i1 / i2 << endl;

    cout << endl << "===== Ex 5.25 ====" << endl;
    cout << "Input two integer i3, i4 then divide i3/i4: " << endl;

    int i3, i4;
    cin >> i3 >> i4;

    try {
        if (i4 == 0){
            throw std::runtime_error("the divider should not be zero!!!");
        }
        if (i3 < 0 || i4 < 0){
            throw std::invalid_argument("the divider should be larger than 0!!!");
        }
        cout << "i3 is: " << i3 << endl;
        cout << "i4 is: " << i4 << endl;
        cout << "i3/i4 is: " << i3 / i4 << endl;
    } catch (std::runtime_error err) {
        cout << "This is runtime error." << endl;
        cout << err.what() << endl;
        cout << "Input a non zero divider for i4 agian: " << endl;
        cin >> i4;
        cout << "i3 / non zero i4 now is: " << i3/i4 <<endl;
    } catch (std::invalid_argument err) {
        cout << "This is input argument error." << endl;
        cout << err.what() << endl;
        cout << "Input integer larger than zero again for both i3 and i4: " << endl;
        cin >> i3 >> i4;
        cout << "new i3 / new i4 is: " << i3/i4 << endl;
    }

    cout << "Test if there is output with try catch block." << endl;

    return 0;
}