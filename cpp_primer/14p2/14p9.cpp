#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

int main()
{
    std::string s1 = "0-210-99999-9";
    double d1 =  static_cast<double>(0-210-99999-9);
    Sales_data obj1;
    Sales_data run_time_obj;
    while(std::cin >> run_time_obj){
        obj1.combine(run_time_obj);
    }

    //ex 14.10
    //0-201-99999-9 10 24.95, ok
    //10 24.95 0-210-99999-9, also ok, cuase 0-210-99999-9 will be converted to 0.94999999996, rdstate is still 0, no error
    //aaa 1 aa, is.rdstate() change from 0 to 4, is.failbit is 4; (set to failbit in input operator func), is.fail() now is true

    //output
    /*
    This is non-delegationg constructor initialize members from corresponding arguments.
    Default constructor delegate to nondelegating construtor with three parameters.
    This is non-delegationg constructor initialize members from corresponding arguments.
    Default constructor delegate to nondelegating construtor with three parameters.
    aaa 1 10
    10 24.95 0-210-99999-9
    aaa 1 aa
    This is non-delegationg constructor initialize members from corresponding arguments.
    Default constructor delegate to nondelegating construtor with three parameters.
    Input for Sales_data item failed. Reset Sales_data item to empty //own defined output message
    */
}