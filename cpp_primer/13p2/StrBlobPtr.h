#ifndef STRBLOBPTR
#define STRBLOBPTR
#include <string>
#include <memory>

class StrBlob; //forward declaration

class StrBlobPtr{
friend class StrBlob;
friend bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
friend bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
friend bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
public:
    //first constructor
    StrBlobPtr(): curr(0) {} //implicty initialize wptr to a nullptr
    StrBlobPtr(StrBlob& a, size_t sz = 0):wptr(a.data), curr(sz){}
    //we cannot bind a StrBlobPtr to a const StrBlob object. otherwise wptr always nullptr cause StrBlob class data has no in-class initializer, default to nullptr
    //This restriction follows from the fact that the constructor takes a reference to a nonconst object of type StrBlob.

    //we can defind below constructor for const StrBlob obj,
    //although, now since a is const, its member data is a const shared_ptr,
    //so data should provided in-class initializer, if not, then default initialized to nullptr and cannot be changed again
    //like const share_ptr<vector<string>> data; now data is nullptr,
    //data = make_shared<vector<string>>(); wrong, change data, so if StrBlobStr is const, not much meaning cause wptr and data both null
    StrBlobPtr(const StrBlob& a, size_t sz = 0):wptr(a.data), curr(sz){}


    std::string& deref() const;
    StrBlobPtr& incr();

private:
    //check() return a shared_ptr to the vector in StrBlob object if the check succeeds
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string&) const;

    //store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;

    std::size_t curr; //current position within the array
};

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs);

#endif