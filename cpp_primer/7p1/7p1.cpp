#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cassert>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

using std::cin;
using std::cout;
using std::endl;

using std::string;
using std::vector;

int main()
{
    string ss = "bbb";
    string &ssrf = ss;
    string ss2 = "aaa";
    string &ssrf2 = ss2;
    Sales_data total(ss); // object total to hold accumulated data;
    Sales_data trans(ssrf2); // object trans to hold each time read in data;

    // ===================== Constructor Experiment Start =====================
    // we need to make bookNo, units_sold, revenue public member if we want to do below experiment
    // if (total.bookNo == trans.bookNo){
    //     cout << "Initial total.bookNo equals trans.book.No : " << total.bookNo << endl;
    // } else {
    //     cout << "Initial total.bookNo is: " << total.bookNo << ", trans.bookNo is: " << trans.bookNo << endl;
    // }
    // // trans only use aaa initialize bookNo
    // cout << "trans.units_sold is: " << trans.units_sold << endl; // 0
    // cout << "trans.revenue is: " << trans.revenue << endl; // 0

    // // if want to use default initializer, should use Sales_data trans_1; not Sales_data trans_1();
    // Sales_data trans_1;
    // cout << "trans_1 bookNo is: " << trans_1.bookNo << endl; // empty string
    // cout << "trans_1 units_sold is: " << trans_1.units_sold << endl; // 0
    // cout << "trans_1 revenue is: " << trans_1.revenue << endl; // 0

    // Sales_data trans_2(3, 5); //matching overloaded Sales_data(unsigned int x, double y)
    // cout << "trans_2 bookNo is: " << trans_2.bookNo << endl; // empty string
    // cout << "trans_2 units_sold is: " << trans_2.units_sold << endl; // 3
    // cout << "trans_2 revenue is: " << trans_2.revenue << endl; //5

    // //using  istream& constructor in header
    // Sales_data trans_3(cin); // for example input: newnew 10 100; no need ctrl-D, hit enter then it will continue output when detect 3 inputs
    // cout << "trans_3 bookNo is: " << trans_3.bookNo << endl; // the first input newnew
    // cout << "trans_3 units_sold is: " << trans_3.units_sold << endl; // the second input 10
    // cout << "trans_3 revenue is: " << trans_3.revenue << endl; // 10*100 = 1000
    // ===================== Constructor Experiment End =====================

    // if using /2p6/Sales_data_copy.h, which read is defined inside class, then calling read() should change to total.read() and trans.read()
    if (read(cin, total)) // read first transaction
    {
        while(read(cin, trans)) // read remaining transaction
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(cout, total); // print total transaction in one kind isbn book
                cout << endl;
                total = trans; // initialize total to the different ISBN trans
            }
        }
        // after cin ends; the last trans has not been print yet
        print(cout, total);
        cout << endl;
    }
    else
    {
        std::cerr << "No data?!" << endl;
    }
    return 0;
}