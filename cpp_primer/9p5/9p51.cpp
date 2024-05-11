#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class date_f{
public:
    unsigned year;
    unsigned month;
    unsigned day;

private: //process implementation keep private
    void process(std::string str_process);

public: // constructor need to be public
    explicit date_f(std::string str){
        process(str);
    }

};

struct month_match{
    std::string month;
    int i;

    //month_match(std::string str, int some_i){month = str; i = some_i;}
    month_match(std::string str, int some_i): month(str), i(some_i) {}
};

std::vector<month_match> mm = { {"Jan", 1},     {"January", 1},
                                {"Feb", 2},     {"Feburary", 1},
                                {"Mar", 3},     {"March", 3},
                                {"Apr", 4},     {"April", 4},
                                {"May", 5}, 
                                {"Jun", 6},     {"June", 6},
                                {"Jul", 7},     {"July", 7},
                                {"Aug", 8},     {"August", 8},
                                {"Seq", 9},     {"September", 9},
                                {"Oct", 10},    {"October", 10},
                                {"Nov", 11},    {"November", 11},
                                {"Dec", 12},    {"December", 12},
};


void date_f::process(std::string str_process)
{
    /* example of str_process
    January 1, 1900
    1/1/1900
    Jan 1, 1900
    */
    std::string seperator = ", /"; //seperator is ',' space or '/'
    std::string::size_type pos = 0;
    while((pos = str_process.find_first_of(seperator, pos)) != std::string::npos){
        str_process[pos] = ' '; //repalce all the seperator to space
        ++pos;
    }

    std::stringstream stream_s(str_process); //string stream to hold processed string like "Aug 29 1995"

    std::string s_year, s_month, s_day; //string to store each word in string stream

    stream_s >> s_month >> s_day >> s_year; //note the sequence in string strem is month then day then year

    //find corresponding integer for month string
    for(auto item : mm){
        if(s_month == item.month){
            month = item.i;
            break;;
        }
    }

    //convert string to int
    year = stoi(s_year);
    day = stoi(s_day);
}

int main()
{
    std::vector<std::string> vec_s = {// test string are as follows
        "January 1, 1900",
        "1/1/1900",
        "Jan 1, 1900",
        "Aug/29/1995"
    };

    //use each string element in vec_s to constuct a date_f element
    std::vector<date_f> vec_date_f;

    for(auto item : vec_s){
        date_f element(item); //construct element using string item
        vec_date_f.push_back(element);
    }

    //now check vec_date_f element has the right unsigned year month day
    for(decltype(vec_date_f.size()) i = 0; i < vec_date_f.size(); ++i){
        std::cout << "vec_date_f[" << i << "]'s member value month/day/year are: " << vec_date_f[i].month << " "
                                                                                   << vec_date_f[i].day << " "
                                                                                   << vec_date_f[i].year << " "
                                                                                   << std::endl;
    }

    return 0;
}