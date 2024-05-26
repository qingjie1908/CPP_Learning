#include <string>
#include <vector>
#include <iostream>
#include <time.h>


class numbered{
public:
    numbered(){++unique_num; mysn = "SN" + std::to_string(unique_num);};
    numbered(const numbered& orig){++unique_num; mysn = "SN" + std::to_string(unique_num);}

    static int unique_num; //non-const static member cannot have in-class initializer
    std::string mysn;

};
int numbered::unique_num = 0;


void f(numbered s) {std::cout << s.mysn << std::endl;}

void f_ref(numbered& s) {std::cout << s.mysn << std::endl;}

void f_const_ref(const numbered& s) {std::cout << s.mysn << std::endl;}

int main()
{
    /*
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
    //if no copy constructor, out put SN1, SN1, SN1
    //if copy constructor, output SN4, SN5, SN6, cause calling f the paramenter s using copy control constructor
    */

   /*
   numbered a, b = a, c = b;
   f_ref(a);
   f_ref(b);
   f_ref(c);
   //output: SN1, SN2, SN3
   */

   numbered a, b = a, c = b;
   f_const_ref(a);
   f_const_ref(b);
   f_const_ref(c);
    //output: SN1, SN2, SN3





    
}