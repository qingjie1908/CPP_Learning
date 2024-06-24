#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/15p93/QueryResult.h"

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