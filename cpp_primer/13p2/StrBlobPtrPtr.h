#ifndef STRBLOBPTRPTR
#define STRBLOBPTRPTR
#include <string>
#include <vector>
#include <memory>

class StrBlobPtr;
class StrBlob;

class StrBlobPtrPtr{
friend class StrBlobPtr;
friend class StrBlob;
public:
    StrBlobPtrPtr():p_sbp(nullptr){}
    StrBlobPtrPtr(StrBlobPtr& sbp):p_sbp(&sbp){}

    StrBlobPtr& operator*();
    StrBlobPtr* operator->();

    //note if we define StrBlobPtr& operator->() {return operator*();}
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
private:
    StrBlobPtr* p_sbp;

};

#endif