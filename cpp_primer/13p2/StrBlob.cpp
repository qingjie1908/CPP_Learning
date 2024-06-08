#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlob.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p2/StrBlobPtr.h"


//constructor
//Initialize its data member to point to a dynamically allocated vector. 
//The default constructor allocates an empty vector:
StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il)){}

//copy constructor
StrBlob::StrBlob(const StrBlob& orig)
{
    //copy value, which is the vector orig.data pointed to
    data = std::make_shared<std::vector<std::string>> (*orig.data);
}

//copy assignment operator
//should consider self assignment
//lhs should allocated a new memory with same contents even if lhs and rhs are the same (self assignment) for most cases
//but for this case, lhs data pointer should not be updated to a new address
//cause we have StrBlobPtr obj which hould weak_ptr to this obj shared_ptr data
//if we update the lhs pointer value, then the weak_ptr.lock() is false, since that memory is freed
//we cannot access the vector through StrBlobPtr anymore
//so we only update the pointed value, not the pointer it self
StrBlob& StrBlob::operator=(const StrBlob& rhs)
{
    //bad case for StrBlob beacuse we have StrBlobPtr need to tie StrBlob through weak_ptr
    /*
    //first create a temp memory to hold rhs contents
    auto temp = std::make_shared<std::vector<std::string>> (*rhs.data);

    //now free the lhs orginal hold memory, and 
    data = temp; //temp is detroyed after call =; then data is the only shared ptr point to new memory with contents of rhs
    return *this;
    */

    //only update pointed value, not pointer it self, in order not invalidated StrBlobPtr obj
    *data = *rhs.data;
    return *this;

}

void StrBlob::check(size_type i, const std::string &msg) const {
        if (i >= data->size())
            throw std::out_of_range(msg);
}

std::string StrBlob::front(){
    // if the vector is empty,check will throw 
    check(0, "front on empty StrBlob");
    std::string result = "non-const version front: " + data->front();
    return result;
}

std::string StrBlob::front() const{
    // if the vector is empty,check will throw 
    check(0, "front on empty StrBlob"); 
    std::string result = "const version front: " + data->front();
    return result;
}

std::string StrBlob::back(){
    check(0, "back on empty StrBlob");
    std::string result = "non-const version back: " + data->back();
    return result;
}

std::string StrBlob::back() const{
    check(0, "back on empty StrBlob");
    std::string result = "const version back: " + data->back();
    return result;
}

void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

StrBlobPtr StrBlob::begin()
{
    return StrBlobPtr(*this); //use the second construtor, which the curr is defautl = 0, point to first element in vector data point to
}

StrBlobPtr StrBlob::begin() const
{
    return StrBlobPtr(*this); //use the second construtor, which the curr is defautl = 0, point to first element in vector data point to
}

StrBlobPtr StrBlob::end()
{
    return StrBlobPtr(*this, data->size()); //use the second construtor, which the curr = obj a.data->size(),
}

StrBlobPtr StrBlob::end() const
{
    return StrBlobPtr(*this, data->size()); //use the second construtor, which the curr = obj a.data->size(),
}


bool operator==(const StrBlob& lhs, const StrBlob& rhs){
    return (*(lhs.data) == *(rhs.data)); //use std::vector == operator
}

bool operator!=(const StrBlob& lhs, const StrBlob& rhs){
    return !(lhs == rhs); //use class == operator
}

bool operator<(const StrBlob& lhs, const StrBlob& rhs){
    return (*(lhs.data) < *(rhs.data)); //use std::vector < operator
}