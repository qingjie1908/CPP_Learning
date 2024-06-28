#ifndef BLOBPTR
#define BLOBPTR

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/16p1/Blob.h"

template<typename T>
class BlobPtr;

template<typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);
//cause here we need BlobPtr<T> as parameter, so need templacte class BlobPtr forward declartion here

template<typename T>
bool operator<(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);

template<typename T>
class BlobPtr{
friend bool operator== <>(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);
//friend bool operator< <>(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);
friend bool operator< <T>(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);
//use both operator< <> or operator< <T> are ok, it can be deduced

public:
    BlobPtr():wp_blob(nullptr), curr(0){}
    BlobPtr(const Blob<T>& Blob_obj, size_t sz = 0):wp_blob(Blob_obj.data), curr(sz){}

    T& operator*() const{
        auto ret = check(curr, "derefence out of range");
        return (*ret)[curr];
    }

    BlobPtr& operator++();
    BlobPtr& operator--();
    BlobPtr operator++(int);
    BlobPtr operator--(int);




private:
    std::weak_ptr<std::vector<T>> wp_blob;
    std::size_t curr;

    std::shared_ptr<std::vector<T>>
    check(std::size_t i, const std::string& msg) const;
};



template<typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string& msg) const{
    auto sp = wp_blob.lock();
    if(!sp){ //sp is null shared_ptr
        throw std::runtime_error("unbound StrBlobPtr");
    }

    if(i >= sp->size()){
        throw std::out_of_range(msg);
    }

    return sp;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    check(curr, "increment past end of BlobPtr");
    //if curr not point to past end, continue
    ++curr;
    return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    --curr; //curr is size_t, unsigned, if it's 0, --curr will be a very large number
    check(curr, "decrement past begin of BlobPtr");
    //--curr still valid, continue
    return *this;
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    auto ret = *this; //get old state
    //update this
    ++(*this);
    return ret; //return old state
}

template<typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    auto ret = *this; //get old state
    //update this
    --(*this);
    return ret; //return old state
}

//non-member friend func
template<typename T> inline
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs){
    //weak_ptr have no ==
    //return lhs.wp_blob == rhs.wp_blob && lhs.curr == rhs.curr;

    //shared_ptr have ==
    return lhs.wp_blob.lock() == rhs.wp_blob.lock() && lhs.curr == rhs.curr;

}

template<typename T> inline
bool operator<(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs){
    return lhs.wp_blob.lock() == rhs.wp_blob.lock() && lhs.curr < rhs.curr; //only pointed to same vec memory, then compare curr
}
#endif