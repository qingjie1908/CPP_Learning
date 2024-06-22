#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p91/Query.h"

//non-member function
void generate_vec_file(std::ifstream& in_f, std::shared_ptr<std::vector<std::string>>& vec_file_sp_r){ //shared_ptr vec_file_sp pass by reference
    std::string read_line;
    while(getline(in_f, read_line)){
        vec_file_sp_r->push_back(read_line);
    }
}

//non-member function
void generate_map(std::shared_ptr<std::vector<std::string>>& vec_file_sp_r, std::set<int>& line_record_r, std::map<std::string, std::set<int>>& word_line_map_r, std::map<std::string, int>& word_count_map_r){
    auto iter = (*vec_file_sp_r).begin();
    int line_number = 1; // let line number start from 1
    while(iter != (*vec_file_sp_r).end()){
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
TextQuery::TextQuery(std::ifstream &input_f): 
            input_file(input_f),
            vec_file_sp(std::make_shared<std::vector<std::string>>()),
            line_record({}),
            word_line_map({}),
            word_count_map({})
            {
                generate_vec_file(input_file, vec_file_sp);
                generate_map(vec_file_sp, line_record, word_line_map, word_count_map);
            }


//member func query
QueryResult TextQuery::query(const std::string& find_word) const {

    //creat a shared_ptr so that memory can be shared to QueryResult class obj
    //note result should contain two part, first line number, seconde line result
    //so p_hold is a vec, each element is a pair of <line_number, string_line>
    //p_hold now point to empty vec
    std::shared_ptr<std::vector<std::pair<int, std::string>>> p_hold = std::make_shared<std::vector<std::pair<int, std::string>>> ();

    //also create another share ptr hold this word occurence in the whole file
    std::shared_ptr<int> occurrence = std::make_shared<int>(0); //initialized to 0
    

    //use p_hold and occurrence to construct a QueryResult class obj, also pass vec_file_sp, so QueryResult has access to orginall input file
    QueryResult obj(p_hold, occurrence, vec_file_sp);

    if(word_line_map.count(find_word)){ //there is a word in this file

        //word_line_map[find_word] is its corresponding set holding line number
        //find each line in vec_file using this line number

        //since subscirpt[] may add element if it's not exist, use .at(key)
        for(auto line_number : word_line_map.at(find_word)){
            p_hold->push_back({line_number, (*vec_file_sp)[line_number-1]}); //push back a pair {line_number, line_string}
        }

        //find this find_word occurence in word_count map
        *occurrence = word_count_map.at(find_word);

    }
    //else then not find, p_hold and p_result are still empty vec, occurrence is 0

    return obj; 

} // after call query(), p_hold, occurrence destroyed, but p_result and p_occur in returned obj that call this query() func still exist

//non-member func print
std::ostream& print(std::ostream& os, QueryResult& result_obj){
    //first check if there is any result
    if(!result_obj.p_result->empty()){
        //first print the word occurence in the whole file
        os << "element occurs " << *result_obj.p_occur << " times: " << std::endl;

        //then print each line that contains this word
        auto curr = result_obj.p_result->begin();
        while(curr != result_obj.p_result->end()){
            os << "\t" << "(line " << curr->first << ") " << curr->second << std::endl;
            ++curr;
        }
    } else {
        //os << "not find this element." << std::endl;
    }
    return os;
}

//non-member func
//need access NotQuery private constructor, make it friend to class NotQuery
Query operator~(const Query& orig){
    //return Query(std::shared_ptr<Query_base>(new NotQuery(orig)));
    //below one implicitly uses the Query constructor
    return std::shared_ptr<Query_base>(new NotQuery(orig));
    //equal to following 
    //std::shared_ptr<Query_base> tmp (new NotQuery(orig))
    //return Query(tmp); //use the Query constructor that takes a shared_ptr
}

//member func
QueryResult NotQuery::eval(const TextQuery& t) const {
    QueryResult has_q = query.eval(t);

    //get whole input file size, number of lines in this file, which is used as line number check
    auto size_file = has_q.p_file->size();

    //has_q.p_result hold line number and corresponding string line,
    //line number start from 1, so check if line number is in [1, size_file]
    //note, has_q.p_result line_number is ascending order, and it's a subset of of [1, size_file]

    //so example has_q.p_result {{3, "asd"}, {5, "sdagt"}};
    //has_q.p_file is {"asf", "tty", "asd", "43ty", "sdagt", "ertqw"};
    
    //Generate a new QueryResult no_has_q, no_has_q.p_result {{1, "asf"}, {2, "tty"}, {4, "43ty"}, {6, "ertqw"}}
    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_not_result;
    auto curr = has_q.p_result->begin(); //curr refer to a pair like {3, "asd"}
    auto end = has_q.p_result->end();
    for(decltype(size_file) check_line = 1; check_line <= size_file; ++check_line){
        if(curr != end && curr->first == check_line){ //match, not add this line into new_result_vec_sp
            //advance check_line, advance curr
            ++curr;
        } else if(curr != end && curr->first != check_line) { //not match, add this line into new_result_vec_sp
            sp_new_not_result->push_back({check_line, (*(has_q.p_file))[check_line - 1]});
            //advance check_line, not doing for curr
        } else { // curr go to end; add remaning in has_q.p_file into new_result_vec_sp
            sp_new_not_result->push_back({check_line, (*(has_q.p_file))[check_line - 1]});
        }
    }

    //return new QueryResult no_has_q,
    return QueryResult(sp_new_not_result, has_q.p_occur, has_q.p_file);
}

Query operator&(const Query& lhs, const Query& rhs){
    //generator a AndQuery object, use &AndQuery to construct a Query object hold AndQuery pointer
    return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));  
}

QueryResult AndQuery::eval(const TextQuery& t) const{
    QueryResult lhs_result = lhs.eval(t);
    QueryResult rhs_result = rhs.eval(t);

    //lhs_result: {{1, "asa"}, {2, "bbs"}}; occur n1 times in file
    //rhs_result: {{2, "bbs"}, {3, "xwe"}}; occur n2 times in file

    //And only get {{2, "bbs"}} into new result

    std::set<int> lhs_line_number, rhs_line_number;
    for(auto item : *(lhs_result.p_result)){ //item is like pair {1, "asa"}
        lhs_line_number.insert(item.first);
    }
    for(auto item : *(rhs_result.p_result)){
        rhs_line_number.insert(item.first);
    }
    //now set lhs and rhs set is {1, 2} and {2, 3}
    //get final set {2}
    std::set<int> new_and_set;

    std::set_intersection(lhs_line_number.begin(), lhs_line_number.end(), rhs_line_number.begin(), rhs_line_number.end(),
                            std::inserter(new_and_set, new_and_set.begin()));

    //now new_and_set is {2}, push_back input file index at 1

    //std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_or_vec_result; //not initialized, nullptr, dereference is dangerous
    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_or_vec_result = std::make_shared<std::vector<std::pair<int, std::string>>>(); //initialize to empty vec
    for (auto line_number : new_and_set){
        sp_new_or_vec_result->push_back({line_number, (*(lhs_result.p_file))[line_number - 1]});
    }

    std::shared_ptr<int> sp_new_and_occur = std::make_shared<int>(0); //need initialized to 0, otherwise nullptr
    (*sp_new_and_occur) = new_and_set.size();

    return QueryResult(sp_new_or_vec_result, sp_new_and_occur, lhs_result.p_file);
}

Query operator|(const Query& lhs, const Query& rhs){
    return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery& t) const{
    QueryResult lhs_result = lhs.eval(t); //here lhs rhs are type Query, need to include Query.h
    QueryResult rhs_result = rhs.eval(t);
    //note lhs rhs can also And/Or/Not/Word Query type, so should include all header file
    //when call eval, go to call eventually word query, then to call TextQuery::query() so need to include "TextQuery" header file

    //lhs_result: {{1, "asa"}, {2, "bbs"}}; occur n1 times in file
    //rhs_result: {{2, "bbs"}, {3, "xwe"}}; occur n2 times in file

    //merge, and remove duplicate

    //first get merged line_number into set,
    //then use that to get string_line in input file

    std::set<int> merge_line_number;
    for(auto item : *(lhs_result.p_result)){ //item is like pair {1, "asa"}
        merge_line_number.insert(item.first);
    }
    for(auto item : *(rhs_result.p_result)){
        merge_line_number.insert(item.first);
    }
    //now set merge_line_number is 1,2,3
    //get corresponding string_line in input file (subsrcipt index is 0,1,2)

    std::shared_ptr<std::vector<std::pair<int, std::string>>> sp_new_or_result = std::make_shared<std::vector<std::pair<int, std::string>>>();

    for(auto line_number : merge_line_number){
        sp_new_or_result->push_back({line_number, (*(lhs_result.p_file))[line_number - 1]});
    }

    //for p_occrence
    std::shared_ptr<int> sp_new_or_occur = std::make_shared<int>(0);

    *sp_new_or_occur = merge_line_number.size();

    return QueryResult(sp_new_or_result, sp_new_or_occur, lhs_result.p_file);

}
