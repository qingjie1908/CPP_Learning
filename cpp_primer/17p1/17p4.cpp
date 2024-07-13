#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <algorithm>
#include <numeric> //for std::accumulate
#include <map>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/2p6/Sales_data.h"

bool compareIsbn(const Sales_data& lhs, const Sales_data& rhs){
    return lhs.bookNo < rhs.bookNo;
}


typedef std::tuple<std::vector<Sales_data>::size_type, 
                    std::vector<Sales_data>::const_iterator, 
                    std::vector<Sales_data>::const_iterator> matches;

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>>& files,
                 const std::string& book)
{
    std::vector<matches> ret;

    for(auto it = files.cbegin(); it != files.cend(); ++it){
        //By default, equal_range uses the < operator to compare elements. 
        //Because Sales_data does not have a < operator, we pass a pointer to the compareIsbn function
        auto pair_iter = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (pair_iter.first != pair_iter.second){ //there is a match in this store for "book"
            ret.push_back(std::make_tuple(it - files.cbegin(), pair_iter.first, pair_iter.second));
        }
    }

    return ret;
}

void reportResults(std::istream& in, std::ostream& os, const std::vector<std::vector<Sales_data>>& files)
{
    std::string s; //book name to look for
    while (in >> s){
        auto ret = findBook(files, s);
        if (ret.empty()){
            std::cout << s << " not found in any stores" << std::endl;
            continue;
        }
        for(auto it = ret.begin(); it != ret.end(); ++it){ //it pointed to one store holding results
            os << "store No." << std::get<0>(*it) << " sales: "
            //Because Sales_data defines the addition operator, we can use the library accumulate algorithm to sum the transactions
            //initial value is Sales_data(s), which is an object of unit_sold and revenue are both 0
                << std::accumulate(std::get<1>(*it), std::get<2>(*it), Sales_data(s))
                << std::endl;

        }
    }
}

//ex 17p5
typedef
std::pair<std::vector<Sales_data>::size_type, 
                      std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator>>
matches2;

std::vector<matches2>
findBook2(const std::vector<std::vector<Sales_data>>& files,
                 const std::string& book)
{
    std::vector<matches2> ret;

    for(auto it = files.cbegin(); it != files.cend(); ++it){
        //By default, equal_range uses the < operator to compare elements. 
        //Because Sales_data does not have a < operator, we pass a pointer to the compareIsbn function
        auto pair_iter = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (pair_iter.first != pair_iter.second){ //there is a match in this store for "book"
            ret.push_back(std::make_pair(it - files.cbegin(), std::make_pair(pair_iter.first, pair_iter.second)));
        }
    }

    return ret;
}

//ex 17p6
typedef 
std::map<std::vector<std::vector<Sales_data>>::size_type, std::vector<Sales_data>::size_type> //first which store, then second in the store which book is wanted name
matches3;

matches3
findBook3(const std::vector<std::vector<Sales_data>>& files,
                 const std::string& book)
{
    matches3 ret;

    for(auto it = files.cbegin(); it != files.cend(); ++it){
        //By default, equal_range uses the < operator to compare elements. 
        //Because Sales_data does not have a < operator, we pass a pointer to the compareIsbn function
        auto pair_iter = std::equal_range(it->cbegin(), it->cend(), book, compareIsbn);
        if (pair_iter.first != pair_iter.second){ //there is a match in this store for "book"
            ret[it - files.cbegin()] = pair_iter.first - it->cbegin();
            //for example, key is which store, value is in this store, which book name is we wanted
        }
    }

    return ret;
}

