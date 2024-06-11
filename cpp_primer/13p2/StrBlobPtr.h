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
    StrBlobPtr(StrBlob& a, size_t sz = 0);
    //we cannot bind a StrBlobPtr to a const StrBlob object. otherwise wptr always nullptr cause StrBlob class data has no in-class initializer, default to nullptr
    //This restriction follows from the fact that the constructor takes a reference to a nonconst object of type StrBlob.

    //we can defind below constructor for const StrBlob obj,
    //although, now since a is const, its member data is a const shared_ptr,
    //since data has not provided in-class initializer, if not, then default constructor initialized data to nullptr and cannot be changed again, 
    //now data is nullptr, derefence it is error, unless we use the initializer list constructor
    StrBlobPtr(const StrBlob& a, size_t sz = 0);


    std::string& deref() const;
    StrBlobPtr& incr();

    std::string& operator[](std::size_t n);
    const std::string& operator[](std::size_t n) const;
    //prefix ++, --
    StrBlobPtr& operator++();
    StrBlobPtr& operator--();
    //postfix ++,--
    //postfix operators should return the old (unincremented or undecremented) value
    //That value is returned as a value, not a reference
    StrBlobPtr operator++(int); //compiler supplies 0 to int, we can but we should not use this int parameter
    StrBlobPtr operator--(int);

    StrBlobPtr& operator-(size_t n);
    StrBlobPtr& operator+(size_t n);

    std::string& operator*() const;
    std::string* operator->() const;
    //operator -> delegate work to own operator*
    //operator->() must return pointer to class type (std or own defined class)
    //or an object of a class type that defined own operator, in this case, repeat previous step
    //at last, class_obj->mem is used as *(returned result).mem
    //here return string* sp, then class_obj->size() means (*s_p).size()
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
//bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs); not define < operator for pointer

#endif