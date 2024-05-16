#include <iostream>
#include <vector>
#include <string>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/1p5/Sales_item.h"
#include <numeric> //for accumulate

int main()
{
    std::istream_iterator<Sales_item> is_iter(std::cin), is_iter_eof;
    std::ostream_iterator<Sales_item> os_iter(std::cout, "\n");

    std::vector<Sales_item> vec_S;

    //read from std::cin, then vec_S.push_back(*is_iter);
    std::copy(is_iter, is_iter_eof, std::insert_iterator(vec_S, vec_S.begin()));

    //now vec_S hold Slaes_item
    //Sales_item{ string bookNo, int units_sold, double price}
    //sort them accordring bookNo string
    std::sort(vec_S.begin(), vec_S.end(), [](Sales_item obj1, Sales_item obj2){return obj1.isbn() < obj2.isbn();});

    //now vec_S hold transaction with same bookNo consecutively
    
    auto curr = vec_S.begin();
    auto prev = vec_S.begin();

    while(curr != vec_S.end()){
        //first, use std::find() find the first element of which the bookNo is different
        //find take unary predicate, return iter to first different element
        curr = std::find_if(prev, vec_S.end(), [curr](Sales_item obj){return obj.isbn() != curr->isbn();});

        //now curr point to first different element of new isbn
        //we need to add the previous element with same isbn and print to std::cout
        //note [prev, curr) in iterator range 
        //now temp = sum of Sales_items with same isbn, + operatir is defined in Sales item header
        //be careful that += in header not inlcude bookNo
        Sales_item temp(prev->isbn()); //create a temp empty object as a start to hold the sum of Sales_item, construct with bookNo, which is the same bookNo element of first segment
        os_iter = std::accumulate(prev, curr, temp);
        //now os_iter = sum of same isbn sales item,
        //then std::cout << *os, include newline, Sales_item header also define << operator

        //now we need to update prev to point to next segment of new isbn()
        prev = curr;

        return 0;

    }

    //input int std::cin
    /*
    A 1 2.0
    A 2 2.5
    B 1 3.0
    C 2 4.0
    A 3 2.2
    C 4 4.5
    B 5 3.2
    */ // then ctrl+D

    //output
    /*
    A 6 13.6 2.26667
    B 6 19 3.16667
    C 6 26 4.33333
    */
}
