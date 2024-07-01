#ifndef MYVEC
#define MYVEC

#include <memory>

template<typename T>
class myVec; //templace class forward declaration in order for friend function parameter

template<typename T>
bool operator==(const myVec<T>& lhs, const myVec<T>& rhs);

template<typename T>
bool operator!=(const myVec<T>&lhs, const myVec<T>& rhs);

template<typename T>
bool operator<(const myVec<T>&lhs, const myVec<T>& rhs);



template<typename T>
class myVec
{
friend bool operator== <>(const myVec<T>& lhs, const myVec<T>& rhs);
friend bool operator!= <>(const myVec<T>&lhs, const myVec<T>& rhs);
friend bool operator< <>(const myVec<T>&lhs, const myVec<T>& rhs);
public:
    myVec():elements(nullptr), first_free(nullptr), cap(nullptr){}
    myVec(const myVec& orig); //copy cosntructor
    myVec& operator=(const myVec& rhs); //copy assignment operator
    ~myVec(); //destructor

    //constructor taks an initialzier_list<std::string>
    myVec(std::initializer_list<T> il);

    //move constructor, take rvalue reference
    myVec(myVec&& orig) noexcept;

    //move assignment operator, take rvalue reference
    myVec& operator=(myVec&& rhs) noexcept;
    //assignment operator take initializer_list
    myVec& operator=(std::initializer_list<T> il);
    //subscript operator, subscript return string element, not StrVec
    T& operator[](std::size_t n);
    const T& operator[](std::size_t n) const;


    void push_back(const T& orig); //copy the element
    //const obj can only call const member func, non-const object can call both const and non-const member func, if overloaded, non-const member func match better
    size_t size() const {return first_free - elements;}
    size_t capacity() const {return cap - elements;}
    T* begin() const {return elements;}
    T* end() const {return first_free;}

    void reserve(size_t n);
    void resize(size_t n, T s = T()); //s can be supplied by user, or default initialized by T()



private:
    T* elements; //point to the first element in allocated memory
    T* first_free; //point just after the last actual element
    T* cap; //point to past the end of allocated memory

    static std::allocator<T> vec_alloc;

    //utility function used by copy constructor, assignment operator and destructor
    std::pair<T*, T*>
    alloc_n_copy(const T* orig_start, const T* orig_end);

    void reallocate(); //will reallocate the StrVec when it runs out of space
    void free(); //destroy the constructed elements and deallocate the memory space
    void chk_n_alloc(){//ensure there is room to add at least one more element into StrVec
        //if there isn't room for another elemnet, chk_n_alloc will call reallocate to get more space
        if (size() == capacity()) {reallocate();}
    }

};

//static member defination
template<typename T> inline
std::allocator<T> myVec<T>::vec_alloc;

template<typename T> inline
std::pair<T*, T*>
myVec<T>::alloc_n_copy(const T* orig_start, const T* orig_end){
    std::size_t orig_size = orig_end - orig_start;
    T* new_begin = vec_alloc.allocate(orig_size);

    //now constructed the new_copy
    //note new_end point to one past end of the last allocated uncontructed memory, left included [new_begin, new_end)
    T* new_end = std::uninitialized_copy(orig_start, orig_end, new_begin);
    
    return {new_begin, new_end};
}

template<typename T> inline
void myVec<T>::free(){

    //cannot deallocate null ptr, default constructor the elements is nullptr, need to check
    if(elements){
        T* curr = first_free;
        while (curr != elements){
            std::allocator_traits<decltype(vec_alloc)>::destroy(vec_alloc, --curr);
        }

        vec_alloc.deallocate(elements, cap - elements);
    }

}

template<typename T> inline
void myVec<T>::reallocate(){
    //when out of original cap, size() = capacity()
    size_t new_capacity = (capacity() == 0 ? 1 : 2 * capacity());

    T* new_begin = vec_alloc.allocate(new_capacity);
    //T* new_end = std::uninitialized_copy(elements, cap, new_begin);

    T* new_curr = new_begin;
    T* old_curr = elements;
    for(std::size_t i = 0; i < capacity(); ++i){
        std::allocator_traits<decltype(vec_alloc)>::construct(vec_alloc, new_curr++, std::move(*(old_curr++)));
    }
    //now new_curr point to one-past-end of the constructed memory

    free();//free old memory
    //update this to new address
    elements = new_begin;
    first_free = new_curr;
    cap = new_begin + new_capacity;
}


template<typename T> inline
myVec<T>::myVec(const myVec& orig){
    std::pair<T*, T*> new_generated = alloc_n_copy(orig.begin(), orig.end());
    elements = new_generated.first;
    first_free = cap = new_generated.second;
}

template<typename T> inline
myVec<T>& myVec<T>::operator=(const myVec<T>& rhs){
    if(this != &rhs){
        std::pair<T*, T*> new_generated = alloc_n_copy(rhs.begin(), rhs.end());
        free();
        elements = new_generated.first;
        first_free = cap = new_generated.second;
    }
    return *this;
}

template<typename T> inline
myVec<T>::~myVec(){
    free();
}

template<typename T> inline
myVec<T>::myVec(std::initializer_list<T> il){
    std::pair<T*, T*> new_generated = alloc_n_copy(il.begin(), il.end());
    elements = new_generated.first;
    first_free = cap = new_generated.second;
}

template<typename T> inline
myVec<T>::myVec(myVec&& orig) noexcept{
    elements = orig.elements;
    first_free = orig.first_free;
    cap = orig.cap;

    orig.elements = orig.first_free = orig.cap = nullptr;
}

template<typename T> inline
myVec<T>& myVec<T>::operator=(myVec<T>&& rhs) noexcept{
    if(this != &rhs){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;

        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

template<typename T> inline
myVec<T>& myVec<T>::operator=(std::initializer_list<T> il){
    free();
    std::pair<T*, T*> new_generated = alloc_n_copy(il.begin(), il.end());
    elements = new_generated.first;
    first_free = cap = new_generated.second;

    return *this;
}

template<typename T> inline
T& myVec<T>::operator[](std::size_t n){
    if(n >= size()){
        throw std::out_of_range("subscript out of range!");
    }
    return elements[n];
}

template<typename T> inline
const T& myVec<T>::operator[](std::size_t n) const{
    if(n >= size()){
        throw std::out_of_range("subscript out of range!");
    }
    return elements[n];
}

template<typename T> inline
void myVec<T>::push_back(const T& orig){
    chk_n_alloc(); //ensure not exceeds capacity
    std::allocator_traits<decltype(vec_alloc)>::construct(vec_alloc, first_free, orig);
    ++first_free;
}

template<typename T> inline
void myVec<T>::reserve(size_t n){
    //if this.capacity() >= n, do nothing
    if(capacity() < n){
        T* new_begin = vec_alloc.allocate(n);
        T* new_end = std::uninitialized_copy(elements, first_free, new_begin);
        free();
        elements = new_begin;
        first_free = new_end;
        cap = elements + n;
    }
}

template<typename T> inline
void myVec<T>::resize(size_t n, T s){ //s can be supplied by user, or default initialized by T()
    if(n < size()){ //need slice down back part
        T* new_start = vec_alloc.allocate(n);
        T* new_curr = new_start;
        T* old_curr = elements;
        for(size_t i = 0; i < n; ++i){
            std::allocator_traits<decltype(vec_alloc)>::construct(vec_alloc, new_curr++, *(old_curr++));
        }
        //now new_curr point to first unconstructed memory, which is also first free and cap
        free();
        elements = new_start;
        first_free = cap = new_curr;
    }
    if(n > size()){ // for exceeds part, use default construction of type T
        T* new_start = vec_alloc.allocate(n);
        T* new_curr = new_start;
        T* old_curr = elements;
        for(size_t i = 0; i < size(); ++i){
            std::allocator_traits<decltype(vec_alloc)>::construct(vec_alloc, new_curr++, *(old_curr++));
        }
        //now new_curr point to first_free (size()), cap is n, first_free < n
        //for remaining part, default construct s = T() or user supplied for s
        //now new_curr is at index = size()
        for(size_t i = size(); i < n; ++i){
            std::allocator_traits<decltype(vec_alloc)>::construct(vec_alloc, new_curr++, s);
        }      
        //now new_curr point to one-past allocated and constructed memory, which is new first_free and cap
        
        free();
        elements = new_start;
        first_free = cap = new_curr;
    }
    //resize() requested same size() as this, do nothing
}

template<typename T> inline
bool operator==(const myVec<T>& lhs, const myVec<T>& rhs){
    if(lhs.size() != rhs.size()) return false;
    for(size_t i = 0; i < lhs.size(); ++i){
        if(lhs[i] != rhs[i]) return false;
    }
    //now size the same, each element also the same
    return true;
}

template<typename T> inline
bool operator!=(const myVec<T>&lhs, const myVec<T>& rhs){
    return !(lhs == rhs);
}

template<typename T> inline
bool operator<(const myVec<T>&lhs, const myVec<T>& rhs){
    if (lhs.size() < rhs.size()) return true;
    if (rhs.size() < lhs.size()) return false;

    for(size_t i = 0; i < lhs.size(); ++i){
        if(lhs[i] < rhs[i]) return true;
        if(rhs[i] < lhs[i]) return false;
        //equal, continue
    }
    //size the same, each element in lhs is same as rhs
    return false;

}

#endif