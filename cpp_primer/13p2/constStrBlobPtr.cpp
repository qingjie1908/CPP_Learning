#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/constStrBlobPtr.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlob.h"

constStrBlobPtr::constStrBlobPtr(): curr(0) {} //implicty initialize wptr to a nullptr
constStrBlobPtr::constStrBlobPtr(const StrBlob& a, size_t sz):wptr(a.data), curr(sz){}

std::shared_ptr<std::vector<std::string>>
constStrBlobPtr::check(std::size_t n, const std::string& msg) const{
    auto p = wptr.lock();
    if(!p){ //p is nullptr
        throw std::runtime_error("unbound StrBlobPtr");
    }
    if(n >= p->size()){
        throw std::out_of_range(msg);
    }

    return p;
}

const std::string& constStrBlobPtr::operator[](std::size_t n) const{
    auto share_p = check(n, "subscirpt out of range");
    //now throw exception, continue
    return (*share_p)[n];
}

const std::string& constStrBlobPtr::operator*() const{
    auto share_p = check(curr, "subscirpt out of range");
    return (*share_p)[curr];
}

const std::string* constStrBlobPtr::operator->() const{
    //delegate to operator*()
    return &(operator*());
}

bool operator==(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs){
    auto share_p_lhs = lhs.wptr.lock();
    auto share_p_rhs = rhs.wptr.lock();
    return share_p_lhs == share_p_rhs && lhs.curr == rhs.curr;
}

bool operator!=(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs){
    return !(lhs == rhs);
}