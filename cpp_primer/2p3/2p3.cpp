#include <iostream>
int main()
{
    int ival = 1024;
    int *pi = &ival;
    std::cout << pi << std::endl; //address of ival

    int **ppi = &pi;
    std::cout << ppi << std::endl; //address of pi

    std::cout << *ppi << std::endl; //address of ival
    

    double dval = 3.14;
    const int &ri = dval;
    std::cout << ri << std::endl;

    std::cout << dval << std::endl;

    dval = 4;
    std::cout << dval << std::endl;

    const double *cptr = &dval;

    int errNumb = 0;
    int *const curErr = &errNumb;

    double ci = 42.1;
    const double *p2 = &ci;
    const int &r = ci;
    std::cout << *p2 << " " << p2 << std::endl;
    std::cout << r << std::endl;
    

    return 0;    
}