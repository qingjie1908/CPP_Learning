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

std::string& StrBlobPtr::operator[](std::size_t n){
    auto share_p = wptr.lock(); //share_p may be nullptr if wptr.expire() is true
    return (*share_p)[n];
}
const std::string& StrBlobPtr::operator[](std::size_t n) const{
    auto share_p = wptr.lock();
    return (*share_p)[n];
}

//prefix ++/--
StrBlobPtr& StrBlobPtr::operator++(){
    //check 'curr' first
    check(curr, "increment past end of StrBlobPtr");
    //if no throw exception, continue
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::operator--(){
    --curr; // if curr is zero,decrementing it will yield an invalid subscript, very large positive value since curr is unsigned int
    check(curr, "decrement past begin of StrBlobPtr");
    return *this;
}

//postfix ++/--, return value, not reference
StrBlobPtr StrBlobPtr::operator++(int){
    StrBlobPtr ret = *this;
    ++*this; //use own define prefix, prefix will check the increment
    return ret;
}

StrBlobPtr StrBlobPtr::operator--(int){
    StrBlobPtr ret = *this;
    --*this;
    return ret;
}

StrBlobPtr& StrBlobPtr::operator-(size_t n){
    curr -= n;
    return *this;
}
StrBlobPtr& StrBlobPtr::operator+(size_t n){
    curr += n;
    return *this;
}

std::string& StrBlobPtr::operator*() const{
    auto shared_p = check(curr, "dereference past end");
    //no throw exception, continue
    return (*shared_p)[curr]; //*shared_p is vector<std::string>  
}
std::string* StrBlobPtr::operator->() const{
    //delegate work to own operator*
    //operator->() must return pointer to class type (std or own defined class)
    //or an object of a class type that defined own operator, in this case, repeat previous step
    //at last, class_obj->mem is used as *(returned result).mem
    //here return string* sp, then class_obj->size() means (*s_p).size()
    return &(operator*()); //operator*() return a string& in vec, then use address of operator to return string address as pointer
}