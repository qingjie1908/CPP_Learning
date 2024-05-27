#include <memory>
#include <string>
#include <vector>
#include <iostream>

class StrBlobPtr;

class StrBlob{
friend class StrBlobPtr; // so that StrBlobPtr can access StrBlob's private member
public:
    typedef std::vector<std::string>::size_type size_type;

    //constructor forward declaration
    StrBlob(); //default constructor
    StrBlob(std::initializer_list<std::string> il);

    //copy constructor
    StrBlob(const StrBlob& orig);

    //copy assignment operator
    StrBlob& operator=(const StrBlob& rhs);

    //A constructor that can be called with a single argument defines an im- plicit conversion from the constructor’s parameter type to the class type,
    // if we use explicit, we cannot use = form, StrBlob b2 = {"a", "an", "the"}; not allowed, should be StrBlob b2( {"a", "an", "the"});

    //const member function to indicate the type *this is const
    //const objeact can only call const memeber function, 
    //if const member func return *this, *this will point to const object
    //then return type should be const reference 
    size_type size() const {return data->size();}

    bool empty() const {return data-> empty();}

    //add or remove elements member func
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();

    //element access member func
    std::string front();
    std::string front() const;

    std::string back();
    std::string back() const;

    //begin and end operation
    //we need forward declartion of class StrBlobPtr,before this, so that begin() and end() knows the return type
    //so that 
    StrBlobPtr begin(); // return StrBlobPtr to first element
    StrBlobPtr end(); // return one past the element

    StrBlobPtr begin() const;
    StrBlobPtr end() const;

    //std::shared_ptr<std::vector<std::string>> data;
    //not need destructor since the only data member is shared ptr, when object go out of scope, shared_ptr manage to freed the memory

private:
    std::shared_ptr<std::vector<std::string>> data; //A default initialized smart pointer holds a null pointer

    //throw msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;

};

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

//====

class StrBlobPtr{
public:
    //first constructor
    StrBlobPtr(): curr(0) {} //implicty initialize wptr to a nullptr
    StrBlobPtr(StrBlob& a, size_t sz = 0):wptr(a.data), curr(sz){}
    //we cannot bind a StrBlobPtr to a const StrBlob object. 
    //This restriction follows from the fact that the constructor takes a reference to a nonconst object of type StrBlob.

    //we can defind below constructor for const StrBlob obj,
    //although 
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

int main()
{
    StrBlob obj1({"a","b","c"}); //data 0x4098
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

    obj2.push_back("d");
    obj1 = obj2;
    //now obj1 vector contents add "d", also its shared_ptr data still 0x4098



}
