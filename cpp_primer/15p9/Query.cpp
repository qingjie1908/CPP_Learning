#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/Query_base.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/15p9/WordQuery.h"

std::ostream& operator<<(std::ostream& os, const Query& q){
    return os << q.rep();
}


