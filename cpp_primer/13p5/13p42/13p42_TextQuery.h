#ifndef TEXTQUERY
#define TEXTQUERY

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>
//#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/StrVec.h"

class QueryResult;

//replace std::vector<string> to StrVec

class TextQuery{
friend void generate_vec_file(std::ifstream& in_f, std::vector<std::string>& vec_f);
friend void generate_map(StrVec& vec_r, std::set<int>& line_record_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r);
friend class QueryResult;
public:
    //constructor declaration, using ifstream to store the input file
    TextQuery(std::ifstream &input_f);

    //member func query(), to find the line for given word
    //return a QueryResult obj
    QueryResult query(std::string find_word);

private:
    std::ifstream& input_file; //note when we pass stream as constructor element, it's a reference, cannot copy

    //first, need to store the file into vector line by line, this is done in constructor
//    StrVec vec_file;

    std::set<int> line_record; //hold the line numbers on which each word appears
    std::map<std::string, std::set<int>> word_line_map; //map, word and its corresponding set holding line number on which word appear
    std::map<std::string, int> word_count_map; //map, word and its occurrence in the file

};


#endif