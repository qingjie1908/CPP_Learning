#include "/Users/qingjie/github/CPP_Learning/cpp_primer/17p1/ex_17p3/QueryResult.h"

//non-member func print
std::ostream& print(std::ostream& os, QueryResult& result_obj, int range_low, int range_high){
    std::string print_head; //print "sentence:"" or "line:"
    if (std::get<3>(result_obj) == 1){
        print_head = "line";
    } else if (std::get<3>(result_obj) == 2){
        print_head = "sentence";
    }

    //first check if there is any result
    if(!std::get<0>(result_obj)->empty()){
        //first print the word occurence in the whole file
        os << "element occurs " << *std::get<1>(result_obj) << " times: " << std::endl;

        //then print each line that contains this word
        auto curr = std::get<0>(result_obj)->begin();
        while(curr != std::get<0>(result_obj)->end()){
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