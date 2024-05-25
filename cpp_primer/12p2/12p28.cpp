#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <memory>

void generate_vec_file(std::ifstream& in_f, std::vector<std::string>& vec_f){
    std::string read_line;
    while(getline(in_f, read_line)){
        vec_f.push_back(read_line);
    }
}

void generate_map(std::vector<std::string>& vec_r, std::set<int>& line_record_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r){
    auto iter = vec_r.begin();
    int line_number = 1; // let line number start from 1
    while(iter != vec_r.end()){
        std::istringstream i_str(*iter); //store a line in i_str
        
        std::string word;
        while(i_str >> word){

            //first process this word
            //because in a file it can be "word", "word, word", word!, word? ...
            std::string punc = "?'!.\",:;";
            size_t pos = 0;
            while((pos = word.find_first_of(punc)) != std::string::npos){
                word.erase(pos, 1); //remove char staring from word[pos] with length 1, so remove one char, return reference to this word
            }


            if(!word_line_map_r.count(word)){ //this word not in the map yet
                //create a pair
                std::pair<std::string, std::set<int>> p = {word, {line_number}};
                word_line_map_r.insert(p);

                //also create its occrence in word_count map
                word_count_map_r[word] = 1;
            } else { //this word already in map, add its line number in set
                (word_line_map_r[word]).insert(line_number);
                //word_line_map_r[word] is its corresponding set
                //not it's not a multiset, so if the same word happens twice in the same line, line_number only record once

                //also update the occurrence of this word
                ++word_count_map_r[word];

            }
        }
        //now the current line process finished
        //move to next line
        ++iter;
        //also remember update its corresponding line_number
        ++line_number;
    }
}

void query(std::string find_word, std::vector<std::string>& vec_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r){

    //note result should contain two part, first line number, seconde line result
    //so p_hold is a vec, each element is a pair of <line_number, string_line>
    //p_hold now is empty vec
    std::vector<std::pair<int, std::string>> p_hold;

    //hold this word occurence in the whole file
    int occurrence = 0; //initialized to 0
    

    if(word_line_map_r.count(find_word)){ //there is a word in this file

        //word_line_map[find_word] is its corresponding set holding line number
        //find each line in vec_file using this line number

        for(auto line_number : word_line_map_r[find_word]){
            p_hold.push_back({line_number, vec_r[line_number-1]}); //push back a pair {line_number, line_string}
        }

        //find this find_word occurence in word_count map
        occurrence = word_count_map_r[find_word];

    }
    //else then not find, p_hold are still empty vec, occurrence is 0

    if(!p_hold.empty()){
        std::cout << "element occurs " << occurrence << " times: " << std::endl;

        auto curr = p_hold.begin();
        while(curr != p_hold.end()){
            std::cout << "\t" << "(line " << curr->first << ") " << curr->second << std::endl;
            ++curr;
        }
    } else {
        std::cout << "not find this element." << std::endl;
    }

    

}


void runQueries(std::ifstream &infile)
{
    //first store file in vec_file
    std::vector<std::string> vec_file; //hold each line in vec_file
    generate_vec_file(infile, vec_file);

    //second, build map
    std::set<int> line_recorder; //for a word, has a set contain line_numbers on which the word appears
    std::map<std::string, std::set<int>> word_line_map; //for each different word in file, store its cooresponding set of line_recorder
    std::map<std::string, int> word_count_map; //for each word in file, count its occurrence
    generate_map(vec_file, line_recorder, word_line_map, word_count_map);

    //run query() on wanted_word


    while(true){
        std::cout << "enter word to look for, or q to quit: " << std::endl;
        std::string s;
        if(!(std::cin >> s) || s == "q") break;
        query(s, vec_file, word_line_map, word_count_map);
    }
    
}


int main()
{
    std::ifstream input_file;
    input_file.open("/Users/qingjie/github/CPP_Learning/cpp_primer/12p2/12p27.txt");

    runQueries(input_file);

    input_file.close();
}
//output:
/*
enter word to look for, or q to quit: 
qingjie
element occurs 7 times: 
        (line 1) this is qingjie
        (line 3) this qingjie! is;
        (line 4) "qingjie is here!
        (line 5) !qingjie;
        (line 6)     "qingjie" with a tab.
        (line 7)     qingjie is qingjie!
enter word to look for, or q to quit: 
is
element occurs 5 times: 
        (line 1) this is qingjie
        (line 2) this is apple;
        (line 3) this qingjie! is;
        (line 4) "qingjie is here!
        (line 7)     qingjie is qingjie!
enter word to look for, or q to quit: 
banana
not find this element.
enter word to look for, or q to quit: 
q
*/