#ifndef STRBLOB
#define STRBLOB

#include <string>
#include <vector>
#include <iostream>

class StrBlobPtr; 

class StrBlob{
friend class StrBlobPtr; // so that StrBlobPtr can access StrBlob's private member
friend bool operator==(const StrBlob& lhs, const StrBlob& rhs);
friend bool operator!=(const StrBlob& lhs, const StrBlob& rhs);
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

//operator ==
bool operator==(const StrBlob& lhs, const StrBlob& rhs);
bool operator!=(const StrBlob& lhs, const StrBlob& rhs);

#endif