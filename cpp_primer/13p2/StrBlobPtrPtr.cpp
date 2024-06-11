#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtrPtr.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlob.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtr.h"

StrBlobPtr& StrBlobPtrPtr::operator*(){
    return *p_sbp;
}
StrBlobPtr* StrBlobPtrPtr::operator->(){
    return &(operator*());
}