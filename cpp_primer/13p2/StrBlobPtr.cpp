#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlob.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtr.h"

std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock(); // is the vector in StrBlob a.data still exists
    if(!ret){ //not exits, a.data use_count = 0; memory freed, vector not avalable
        throw std::runtime_error("unbound StrBlobPtr"); //throw will exit func
    }
    //if ret is not nullptr, then we continue to check size index within range
    //now ret is a shared ptr to a.data, which point to vec string
    if(i >= ret->size()){
        throw std::out_of_range(msg);
    }

    return ret; //if all above two if are ok, then return ret

}

//pointer operation define
std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end"); // p si shared ptr
    //if check success full, no exception will happend in check func
    //can be dereference
    return (*p)[curr]; // return the string in vector that StrBlob object a has
}

//return a reference to the incremented obj
StrBlobPtr& StrBlobPtr::incr()
{
    auto p = check(curr, "increment past end of StrBlobPtr");
    ++curr; //check successful advance current curr in pointer that point to obj a;
    return *this;
}


bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
    //return (lhs.wptr == rhs.wptr); wrong, weak_ptr has no ==

    //convert to shared_ptr to compare
    auto share_p_lhs = lhs.wptr.lock();
    auto share_p_rhs = rhs.wptr.lock();
    return (share_p_lhs == share_p_rhs) && (lhs.curr == rhs.curr);
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs){
    return !(lhs == rhs);
}

//should not define < operator, cause if lhs and rhs are different address
//but they pointed to vector has same contents
//if we compare the vector contents, then both lhs < rhs or rhs < lhs return false
//but lhs == rhs  return false, cause their holding memory address is different
//so conflict with rule: if lhs != rhs, then one must be < than another
//so should not define <