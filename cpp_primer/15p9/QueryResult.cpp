#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/QueryResult.h"

//non-member func print
std::ostream& print(std::ostream& os, QueryResult& result_obj, int range_low, int range_high){
    std::string print_head; //print "sentence:"" or "line:"
    if (result_obj.check_type == 1){
        print_head = "line";
    } else if (result_obj.check_type == 2){
        print_head = "sentence";
    }

    //first check if there is any result
    if(!result_obj.p_result->empty()){
        //first print the word occurence in the whole file
        os << "element occurs " << *result_obj.p_occur << " times: " << std::endl;

        //then print each line that contains this word
        auto curr = result_obj.p_result->begin();
        while(curr != result_obj.p_result->end()){
            if ((curr->first >= range_low) && (curr->first <= range_high)){ //only print results of given range of lines
                os << "\t" << "(" << print_head << " " << curr->first << ") " << curr->second << std::endl;
            }
            ++curr;
        }
    } else {
        //os << "not find this element." << std::endl;
    }
    return os;
}