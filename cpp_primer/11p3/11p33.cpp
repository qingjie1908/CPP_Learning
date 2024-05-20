#include <map>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>

std::map<std::string, std::string> buildMap(std::ifstream &rule_file); //forward declaration

void word_transform(std::ifstream &rule_file, std::ifstream &test_file, std::fstream &result_file)
{
    //first build map from rule_file
    std::map<std::string, std::string> rule_map = buildMap(rule_file);

    //now first copy test file to result file
    //result_file << test_file.rdbuf(); //using mode binary so that the new line and space will be exactly copy into file

    //now process the result file
    std::string word_line;
    while(getline(test_file, word_line)){
        std::stringstream s_str(word_line);
        std::string word;
        std::string new_string; //new_string with updated map value
        while(s_str >> word){
            if(rule_map.find(word) != rule_map.end()){
                word = rule_map[word]; //update word with rule map value
            } else {//else no need to update
                word = word;
            }
            new_string += word + " ";
        }
        //now new_string need to write into result file
        result_file << new_string << std::endl;
    }
}

std::map<std::string, std::string> buildMap(std::ifstream &rule_file)
{
    std::map<std::string, std::string> rule_map; //hold map rule results

    //read from rule_file then create map for each line: map-key map-value
    std::string line_rule_file;
    while(getline(rule_file, line_rule_file)){ //read a line from rule file
        std::istringstream istr(line_rule_file); //istr hole the line
        //first word is key, second part is value
        std::string map_key;
        std::string map_value;
        istr >> map_key; //first word give to map_key
        //now istr hold the second part, start by a leading space
        getline(istr, map_value); //return a remaning strm holds to map_value, include the space after the first word
        //we do not need to clear istr, since it will be destroyed each while loop

        //map value start by a lead space, remove it
        if(map_value.size() >= 2){
            map_value = map_value.substr(1); //if map_value only contain a space, size is 1, then subscript[1] will be undefined behavior
        } else {
            std::cerr << "there is not map rule for key: " << map_key << std::endl;
        }
        

        //now add key and value into rule_map
        rule_map[map_key] = map_value;
        //rule_map.insert({map_key, map_value}); //same effect for map, for multimap it will add value
        //if there is multiple same key, map_key hold the last value
    }

    return rule_map;
}


int main()
{
    std::string word_trans_rule = std::string(std::filesystem::current_path()) + "/" + "word_transformation_rule_11p33.txt";
    std::string test_text = std::string(std::filesystem::current_path()) + "/" + "test_text_11p33.txt";
    std::string result_text = std::string(std::filesystem::current_path()) + "/" + "result_text_11p33.txt";

    std::ifstream if1, if2;
    if1.open(word_trans_rule);
    if2.open(test_text);

    std::fstream iof3; //if3 need both read and write
    iof3.open(result_text, std::fstream::out);


    word_transform(if1, if2, iof3);

    if1.close();
    if2.close();
    iof3.close();
}