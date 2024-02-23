#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string line1, line2;
    line1 = "a";
    line2 = "Z";
    if (line1 < line2) {
        cout << "line1 < line2" << endl;
    } else if (line1 == line2) {
        cout << "line1 = line2" << endl;
    } else {
        cout << "line1 > line2" << endl;
    }

    return 0;
}
