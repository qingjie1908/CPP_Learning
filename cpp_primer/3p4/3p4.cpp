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
    cout << "Input a number of grades between 0 to 100:" << endl;
    vector<int> ivec1; // ivec1 to hold the total grades
    unsigned int a; // a to hold the current input grade
    while (cin >> a) {
        ivec1.push_back(a);
        // hit enter when input finished
        if (cin.get() == '\n') {
            break;
        }
    }

    vector<int> ivec2(11, 0); //initialize the output vector with 11 element;
    
    for (auto n : ivec1) {
        //define which cluster it should be
        decltype(ivec2.size()) index_ivec2 = n/10; // ie grade 90, then ivec2[9] + 1
        ++ivec2[index_ivec2];
    }

    //output the grade cluster
    cout << "The output cluster of grades are: " << endl;
    for (auto n : ivec2) {
        cout << n << " "; // put output in oneline without newline
    }

    cout << endl;

    auto b = ivec2.begin(), e = ivec2.end();

    return 0;
}