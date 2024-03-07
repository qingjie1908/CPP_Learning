#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

string make_plural(size_t ctr, const string &word, const string s1 = "s")
{
    return (ctr > 1) ? word + s1 : word; 
}
char *init(int ht, int wd = 80, char bckgrnd = ' '){return "heel";};

int main()
{

    string res = make_plural(2, "success", "ss");
    // init(24,10);
    cout << res << endl;
    cout << make_plural(2, "success") << endl;
    cout << make_plural(1, "success") << endl;
    cout << make_plural(2, "failure") << endl;

    return 0;
}


