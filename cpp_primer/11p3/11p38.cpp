#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

size_t hasher(const std::string &string_key)
{
    return std::hash<std::string>()(string_key) + 1;
}

bool eqOp(const std::string &string_key1, const std::string &string_key2){
    return string_key1 == string_key2;
}

//==== function for word transform progran
std::unordered_map<std::string, std::string, decltype(hasher) *, decltype(eqOp) * > buildMap(std::ifstream &rule_file); //forward declaration

void word_transform(std::ifstream &rule_file, std::ifstream &test_file, std::fstream &result_file)
{
    //first build map from rule_file
    std::unordered_map<std::string, std::string, decltype(hasher) *, decltype(eqOp) * > rule_map = buildMap(rule_file);

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

    std::cout << "rule_map.bucket_count(): " << rule_map.bucket_count() << std::endl; //61
    std::cout << "rule_map.max_bucket_count(): " << rule_map.max_bucket_count() << std::endl; //288230376151711743
    std::cout << "Number of elements in the 3rd bucket rule_map.bucket_size(3): " << rule_map.bucket_size(3) << std::endl; //0
    std::cout << "Bucket in which elements with non exist key \"a\" would be found. rule_map.bucket(\"a\"): " << rule_map.bucket("a") << std::endl; //43
    std::cout << "Bucket in which elements with exist key \"thk\" would be found. rule_map.bucket(\"thk\"): " << rule_map.bucket("thk") << std::endl; //46

    std::cout << "Average number of elements per bucket rule_map.load_factor(): " << rule_map.load_factor() << std::endl; //0.131148, which equals to 8/61
    std::cout << "Average bucket size that container tries to maintain, rule_map.max_load_factor(): " << rule_map.max_load_factor() << std::endl;// 1
}

std::unordered_map<std::string, std::string, decltype(hasher)*, decltype(eqOp)* > buildMap(std::ifstream &rule_file)
{
    std::unordered_map<std::string, std::string, decltype(hasher) *, decltype(eqOp) * > rule_map(60, hasher, eqOp); //hold map rule results, bucket size 60, when passing function name hasher and eqOp, they accutually pass pointer to this function

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

//====


int main()
{
    //we can directly define unordered containers whose key is one of the built-in types (including pointer types), or a string, or a smart pointer.
    //below is ok
    //std::unordered_map<std::string, size_t> u_map1;

    //we cannot directly define an unordered container that uses a our own class types for its key type
    //Unlike the containers, we cannot use the hash template directly
    //we must supply our own version of the hash template
    //we’ll need to supply functions to replace both the == operator and to calculate a hash code
    //If our class has its own == operator we can override just the hash function, no need eqOps

    //rewrite word counting program
    std::unordered_map<std::string, size_t, decltype(hasher) *, decltype(eqOp) *> u_map1(42, hasher, eqOp); //42 is the bucket size

    std::vector<std::string> vec_s1 = {"a", "a", "aa", "ab", "ba", "b", "ccc", "ba"};
    for (auto item : vec_s1){
        ++u_map1[item];
    }

    for(auto item : u_map1){
        std::cout << item.first << " : " << item.second << std::endl;
    }
    std::cout << "u_map1.bucket_count(): " << u_map1.bucket_count() << std::endl; //43
    std::cout << "u_map1.max_bucket_count(): " << u_map1.max_bucket_count() << std::endl; //384307168202282325
    std::cout << "Number of elements in the 3rd bucket u_map1.bucket_size(3): " << u_map1.bucket_size(3) << std::endl; //0
    std::cout << "Bucket in which elements with key \"a\" would be found. u_map1.bucket(\"a\"): " << u_map1.bucket("a") << std::endl; //15

    std::cout << "Average number of elements per bucket u_map1.load_factor(): " << u_map1.load_factor() << std::endl; //0.139535, which equals to 6/43
    std::cout << "Average bucket size that container tries to maintain, u_map1.max_load_factor(): " << u_map1.max_load_factor() << std::endl;// 1

    //output
    /*
    ccc : 1
    b : 1
    ba : 2
    ab : 1
    aa : 1
    a : 2
    u_map1.bucket_count(): 43
    u_map1.max_bucket_count(): 384307168202282325
    Number of elements in the 3rd bucket u_map1.bucket_size(3): 0
    Bucket in which elements with key "a" would be found. u_map1.bucket("a"): 15
    Average number of elements per bucket u_map1.load_factor(): 0.139535
    Average bucket size that container tries to maintain, u_map1.max_load_factor(): 1
    */

    //rewrite word-transform program
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