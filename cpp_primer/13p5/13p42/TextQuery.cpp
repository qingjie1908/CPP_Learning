#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/13p42/13p42_TextQuery.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/13p42/13p42_QueryResult.h"

//non-member function
void generate_vec_file(std::ifstream& in_f, StrVec& vec_f){
    std::string read_line;
    while(getline(in_f, read_line)){
        vec_f.push_back(read_line);
    }
}

//non-member function
void generate_map(StrVec& vec_r, std::set<int>& line_record_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r){
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

//constructor define
//note generate_vec_file() and generate_map() must be definded before it can be used
//or use forward decalration first then defind after constructor
TextQuery::TextQuery(std::ifstream &input_f): input_file(input_f) {
        generate_vec_file(input_file, vec_file);
        generate_map(vec_file, line_record, word_line_map, word_count_map);

}


//member func query
QueryResult TextQuery::query(std::string find_word){

    //creat a shared_ptr so that memory can be shared to QueryResult class obj
    //note result should contain two part, first line number, seconde line result
    //so p_hold is a vec, each element is a pair of <line_number, string_line>
    //p_hold now point to empty vec
    std::shared_ptr<std::vector<std::pair<int, std::string>>> p_hold = std::make_shared<std::vector<std::pair<int, std::string>>> ();

    //also create another share ptr hold this word occurence in the whole file
    std::shared_ptr<int> occurrence = std::make_shared<int>(0); //initialized to 0
    

    //use p_hold and occurrence to construct a QueryResult class obj
    QueryResult obj(p_hold, occurrence);

    if(word_line_map.count(find_word)){ //there is a word in this file

        //word_line_map[find_word] is its corresponding set holding line number
        //find each line in vec_file using this line number

        for(auto line_number : word_line_map[find_word]){
//            auto start = vec_file.begin();
//            auto str_wanted = *(start + (line_number - 1));
            //p_hold->push_back({line_number, vec_file[line_number-1]}); //push back a pair {line_number, line_string}
//            p_hold->push_back({line_number, str_wanted}); //push back a pair {line_number, line_string}
        }

        //find this find_word occurence in word_count map
        *occurrence = word_count_map[find_word];

    }
    //else then not find, p_hold and p_result are still empty vec, occurrence is 0

    return obj; 

} // after call query(), p_hold, occurrence destroyed, but p_result and p_occur in returned obj that call this query() func still exist
