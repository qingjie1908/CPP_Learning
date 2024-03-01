#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
// #include <initializer_list>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int sumf(std::initializer_list<int> lst)
{
    int sum = 0;
    for (auto iter = lst.begin(); iter != lst.end(); ++iter)
    {
        sum += *iter;
    }
    return sum;
}

int main()
{
    vector<int> lst = {1, 2, 3, 4};
    std::initializer_list<int> lst1 = {1, 2, 3, 4};
    int sum_result;
    sum_result = sumf(lst1);
    cout << sum_result << endl;
    cout << sumf({'q', 2, 3, 4, 5}) << endl;
    return 0;
}

