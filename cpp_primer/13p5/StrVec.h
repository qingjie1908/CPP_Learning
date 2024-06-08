#ifndef STRVEC
#define STRVEC

#include <string>
#include <memory>


/*
    StrVec Memory Allocation Strategyun    
  ┌─┬─┬─┬─┬─┬─┬─┬──────────────────────┐   
  │0│1│2│3│4│5│6│unconstructed elements│   
  └▲└─┴─┴─┴─┴─┴─┘▲─────────────────────┘▲  
   │             │                      │  
   │             │                      │  
elements       first_free               cap
*/


class StrVec{
friend bool operator==(const StrVec& lhs, const StrVec& rhs);
friend bool operator!=(const StrVec&lhs, const StrVec& rhs);
public:
    StrVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
    StrVec(const StrVec& orig); //copy cosntructor
    StrVec& operator=(const StrVec& rhs); //copy assignment operator
    ~StrVec(); //destructor

    //constructor taks an initialzier_list<std::string>
    StrVec(std::initializer_list<std::string> il);

    //move constructor, take rvalue reference
    StrVec(StrVec&& orig) noexcept;

    //move assignment operator, take rvalue reference
    StrVec& operator=(StrVec&& rhs) noexcept;


    void push_back(const std::string& orig); //copy the element
    //const obj can only call const member func, non-const object can call both const and non-const member func, if overloaded, non-const member func match better
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    std::string* begin() const {return elements;}
    std::string* end() const {return first_free;}

    void reserve(size_t n);
    void resize(size_t n, std::string s = "");

private:
    static std::allocator<std::string> alloc; //alloc member will allocate the memory used by StrVec

    std::string* elements; //point to the first element in allocated memory
    std::string* first_free; //point just after the last actual element
    std::string* cap; //point to past the end of allocated memory

    //utility function used by copy constructor, assignment operator and destructor

    std::pair<std::string*, std::string*>
    alloc_n_copy(const std::string* orig_start, const std::string* orig_end); //allocated space and copy a given range of elements

    void reallocate(); //will reallocate the StrVec when it runs out of space
    void free(); //destroy the constructed elements and deallocate the memory space
    void chk_n_alloc(){//ensure there is room to add at least one more element into StrVec
        //if there isn't room for another elemnet, chk_n_alloc will call reallocate to get more space
        if (size() == capacity()) {reallocate();}
    }
};

//static member cannot have in-class initialzier, and will be defined outside of header file
/* below is defination of alloc, defination in header is dangerous

std::allocator<std::string> StrVec::alloc;

//inlcude header in StrVec.cpp
//then include header in 13p5.cpp
//it means you re_define this alloc twice !!!
//when link 13p5.o and StrVec.p, there will be linking error said duplicate symbol
//never write defination in header file!!!

*/

bool operator==(const StrVec& lhs, const StrVec& rhs);
bool operator!=(const StrVec&lhs, const StrVec& rhs);

#endif