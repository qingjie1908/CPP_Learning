#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int factorial(int x)
{
    int result_factorial = 1;
    while (x > 1) {
        result_factorial *= x;
        --x;
    }
    return result_factorial;
}

int absolute(int x)
{
    int result_absolute;
    result_absolute = x < 0 ? -x : x;
    return result_absolute;
}

int main()
{
    cout << "==== Ex 6.5 ====" << endl;
    int x; // input
    int result_factorial, result_absolute; //result of factorial value of x
    cout << "Input a integer number, hit ENTER when finished: " << endl;
    while (cin >> x){ // declare int x, if enter 3.1, then cin first read 3, next read 1 and assign 1 to x;
        if (cin.get() == '\n') {
            break;
        }
    }

    cout << "Output absolute value of input x: " << absolute(x) << endl;

    cout << endl << "==== Ex 6.3 6.4 ====" << endl;
    cout << "Input a integer number, hit ENTER when finished: " << endl;
    while (cin >> x){
        if (cin.get() == '\n') {
            break;
        }
    }
    
    try
    {
        if (x <= 0) {
            throw std::invalid_argument("Invalide argument, input should be larger than 0!");
        }
        result_factorial = factorial(x);
    }
    catch(const std::invalid_argument& e) // using const std::exception& e will match any its subset exception thrown by try, if declare runtime_error and throw invalid_argument in try, then not catch, terminate program
    {
        std::cerr << e.what() << '\n';
        cout << "Please Input interger larger than 0: " << endl;
        cin >> x;
        result_factorial = factorial(x);
    }

    cout << "Output factorial value of input x is: " << result_factorial << endl;
    return 0;
}