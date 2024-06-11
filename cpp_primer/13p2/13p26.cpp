#include <memory>
#include <string>
#include <vector>
#include <iostream>

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlob.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtr.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/constStrBlobPtr.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtrPtr.h"

int main()
{
    StrBlob obj1({"aa","bb","cc"}); //data 0x4098
    StrBlobPtr obj1_ptr(obj1); //wptr 0x4098

    //copy intialized obj2
    StrBlob obj2(obj1); //data 0x4118
    StrBlobPtr obj2_ptr(obj2); //data 0x4118

    //obj1 and obj2 should have the same vector contents but different shared_ptr data member


    //self assignment ob1
    //it should not update pointer value, just update pointed to contents
    //otherwise it will invalidate the StrBlobPtr.weak_ptr
    obj1 = obj1;
    //now obj1 vector contents is same, share_ptr data value not change, still 0x4098

    obj2.push_back("dd");
    obj1 = obj2;
    //now obj1 vector contents add "d", also its shared_ptr data still 0x4098
    std::cout << obj1[2] << " " << obj2_ptr[3] << std::endl; //cc dd

    //++/--
    std::cout << *(obj2_ptr++) << std::endl; //aa
    std::cout << *obj2_ptr << std::endl; //bb
    std::cout << obj2_ptr->front() << std::endl; //b, obj2_ptr-> return string*, then derefence to string, then call string.front()
    std::cout << *(++obj2_ptr) << std::endl; //cc
    std::cout << *(obj2_ptr--) << std::endl; //cc
    std::cout << *obj2_ptr << std::endl; //bb
    std::cout << *(--obj2_ptr) << std::endl; //aa
    std::cout << *(obj2_ptr+2) << std::endl; //cc
    std::cout << *(obj2_ptr-1) << std::endl; //bb

    constStrBlobPtr c_p1(obj2, 1);
    std::cout << *c_p1 << std::endl; //bb
    std::cout << c_p1->back() << std::endl; //b
    std::cout << c_p1[2] << " " << c_p1[1] << std::endl; //cc bb

    //ex 14.32 test StrBlobPtrPtr
    StrBlobPtrPtr p_obj2_ptr(obj2_ptr);
    std::cout << (*(*p_obj2_ptr)).back() << std::endl; //b
    std::cout << p_obj2_ptr->operator->()->back() << std::endl; //b

    //note if we define StrBlobPtr& operator->() {return operator*();} in StrBlobPtrPtr class
    //then when we call this_obj->, it return a class object of StrBlobPtr not a pointer
    //since StrBlobPtr also has overloaded -> operator, it will repeat call its own ->
    //then finnaly return a pointer to string
    //so we can directly call this_obj->back(); which is actually (*string).back

    //if we defind StrBlobPtr* operator->(){return & operator*();}
    //then this_obj-> return a pointer, not a class object, so  equals *(pointer_to_StrBlobPtr).mem
    //then we only call StrBlobPtr member func, not std::string member func;
    //so if we want to achieve same result as above, we need to use this_obj->operator->back();
    //the operator-> is a member func of *(this_obj->()), which is a member func of a StrBlobPtr obj;

    //The overloaded arrow operator must return either a pointer to a class type or an object of a class type that defines its own operator arrow.
    

    return 0;
}
