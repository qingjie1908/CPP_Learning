#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/StrVec.h"

//class static member defination should not be in header, but in implementation cpp file
std::allocator<std::string> StrVec::alloc;

void StrVec::push_back(const std::string& orig){
    chk_n_alloc();
    //the alloc may or may not be updated depending on the capacity

    //now construc element at pos first_free
    //post-fix ++; using original first_free, after this, first_free point to next unconstructed memory
    std::allocator_traits<decltype(alloc)>::construct(alloc, first_free++, orig);

}

std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* orig_start, const std::string* orig_end){
    auto p = alloc.allocate(orig_end - orig_start);
    //now p point to first allocated uncontructed memory

    //now constructed the new_copy
    //note new_end point to one past end of the last allocated uncontructed memory, left included [p, new_end)
    auto new_end = std::uninitialized_copy(orig_start, orig_end, p);

    return {p, new_end};

}

void StrVec::free(){
    //destroy first, then deallocate memory
    //the alloc contain many StrVec objects memory
    //we just destroy and deallocate "this" obj

    //fist record the constructed size of "this" obj
    size_t n = cap - elements;

    // may not pass deallocate a 0 pointer; if elements is 0,there’s no work to do
    //like when we default construct obj, then push_back, it will call free() this empty obj first, then reallocate
    if (elements) {
        for(auto p = first_free; p != elements;){
            std::allocator_traits<decltype(alloc)>::destroy(alloc, --p); //prefix, since first_free point to one-past-end, which is unconstructed memory, cannot be destroy
        }
        //the destroy run the std::string destructor

        alloc.deallocate(elements, n); //n must be the same as the orginal allocated memory (include constructed and unconstructed)
    }

}

//copy control constructor
StrVec::StrVec(const StrVec& orig){

    //use public as possible, this is the interface
    auto result_pair = alloc_n_copy(orig.begin(), orig.end());
    //auto result_pair = alloc_n_copy(orig.elements, orig.first_free);
    elements = result_pair.first;
    first_free = result_pair.second;
    cap = first_free;
}

//desturctor
StrVec::~StrVec(){
    //only free this object from alloc, alloc allocated many StrVec object memory
    free();
}

//copy assignment operator
StrVec& StrVec::operator=(const StrVec& rhs){
    /*
    //create temp StrVec obj then give back to lhs is disaster
    //cause lhs and temp share the same dynamic memory
    //when temp out of scope, lhs dynamic memory will be freed,
    //when lhs out of scope, delete free memory again
    //below is error example code:

    //first create temp hold same contents as rhs
    StrVec temp = rhs; //copy constructor
    //temp.elements is pointer, hold address value of new allocated string

    free(); //free "this" object, call std::string destructor,
    //this object private member still exists

    elements = temp.begin();
    first_free = temp.end();
    cap = first_free;

    //when temp out of scope, StrVec destructor will destroy and free the temp.elemets pointed memory
    //so lhs.elemnts pointed to freed memory, disaster
    //when lhs out of scope, it will delete free memory again!!!
    */
    
    auto pair_result = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = pair_result.first;
    first_free = pair_result.second;
    cap = first_free;

    //when pair-result out of scope, it's just destroy this pair and pair.first .second pointers, the pointer holded value has been copied to "this" object
    //destroy pair does not do any "free memory" action 
    

    return *this;
}

void StrVec::reallocate(){
    //first allocate new larger space for "this" StrVec obj
    auto newcapacity = size() ? 2 * size() : 1; //consider size() = 0

    //new_start_p now point to first unconstructed memory
    auto new_start_p = alloc.allocate(newcapacity);

    //move the data form "this" old memory to the new memory
    auto dest = new_start_p; //point to next free position that hasn't be constructed in new StrVec
    auto elem = elements; //point to next element in old StrVec ("this" StrVec)

    //construct string in new StrVec
    for(size_t i = 0; i != size(); ++i){
        std::allocator_traits<decltype(alloc)>::construct(alloc, dest++, std::move(*elem++)); //post ++, use orignal elem, dest; then ++
    }

    //std::string move constructor: string s1 has pointer a1,  a1 hold address of char[]; string s2, has pointer a2, a2 hold address of same char[]; 
    //&s1 != &s2; &a1 != &a2; but a1 = a2, change string s1 will also change s2 since they share the same char[]
    //so now new memory string and old memory string, their inside pointer member different, but pointed to same char[]

    //after std::move() func, which signal that it wants to use the string move constructor; after move; s1 pointer a1 still exists, but not pointed to char[], *a1 is empty now, now only s2 pointer a2 point to that char[]

    //if not call std::move, use std::string copy consturctor
    //&s1 != &s2; &a1 != &a2; 
    //and most importantly a1 != a2, just the two char[] has same contents
    //so it's like the new char[] is in another address, we are overhead allocating and deallocationg the strings themselves (including the char[]) each time we reallocate


    //new memory constructed finished
    //now free old memory
    free();
    //when free old memory, we destroy the old string object, which just destoy the pointers a1; not destroy a1 pointed char[]
    //cause char[] is not string's member; std::string's member is just pointer a1, which is in a dynamic memory allocated by allocator
    //but its value already store in a2, so we can still access char[] through new memory StrVec object

    //update "this" object from destroyed and deallocated memory to new memory
    elements = new_start_p;
    first_free = dest;
    cap = elements + newcapacity;

}

void StrVec::reserve(size_t n){ //reserve capacity at least n
    auto cur_cap = cap - elements; //current container capacity

    if(cur_cap >= n){ //since this is reserve, not resize, so we should do nothing
        return;
    } else { // we need to allocated more memory
        //first allocate new memory
        auto new_start = alloc.allocate(n); //now we have new memory part can hold n strings
        //new_start point to first un-constructed memory
    
        //now copy from old memory
        auto old_begin = begin();
        auto new_begin = new_start;
        while(old_begin != end()){
            *new_begin = *(old_begin++); //copy string value
            ++new_begin; //new_begin move to next un-constructed memory
        }

        //now free old memory
        free();
        //after free, &(this object) still not change, and still hold elements, first_free, cap members

        //update "this" object from old memory to point to new meory
        elements = new_start;
        first_free = new_begin;
        cap = elements + n;
        
        return;
    }

}

void StrVec::resize(size_t n, std::string s){
//void StrVec::resize(size_t n, std::string s = "") is error, cause it's redined default argument s
//default argument has already provided in class member func declaration 

    //first situation, resize shrink the orignal container
    if(size() > n) {
        // first allocate new memory for n strings
        auto new_start = alloc.allocate(n);
        auto new_begin = new_start;
        if (s != ""){ //we specify the string to initialize resized container
            std::allocator_traits<decltype(alloc)>::construct(alloc, new_start, s);
        } else { // we dont specify, new memory should copy old memory first n strings
            auto old_begin = elements;
            for(size_t i = 0; i < n; ++i){
                *(new_begin++) = *(old_begin++); 
            }
        }
        //now free old memory
        free();

        //update "this" members
        elements = new_start;
        first_free = new_begin; //which actullay is the new vec end
        cap = new_start + n;

        return;
    } else { //second situation, resize increase the capacity
        //note, resize larger n, means this.size() = n, and exceeded elements are value initialied,(need to be constructed)

        //first allocate new memory for n strings
        auto new_start = alloc.allocate(n);
        auto new_begin = new_start;

        auto old_begin = elements;
        //first copy old memory
        while(old_begin != end()){
            *(new_begin++) = *(old_begin++);
        }

        //for extra added memory
        if (s != ""){ // exceeded elements will have s as initial value
            //after this, new_begin pointed to next unconstructed memory
            while(new_begin != (new_start + n)){
                //remaining part intialized to specified s
                *(new_begin++) = s;
            }
        } else { //extra memory value initialized to empty vec
            while(new_begin != (new_start + n)){
                //remaining part intialized to specified s
                *(new_begin++) = "";
            }
        }
        //now new_begin point to off the end of new strvec

        //free old memory
        free();

        //update "this" members
        elements = new_start;
        first_free = cap = new_begin;

        return;
    }
}

//constructor taks an initialzier_list<std::string>
StrVec::StrVec(std::initializer_list<std::string> il){
    size_t n = il.size();

    auto new_start = alloc.allocate(n);
    auto new_begin = new_start;

    for(auto item : il){
        *(new_begin++) = item;
    }

    elements = new_start;
    first_free = cap = new_begin; //off_the_end
}
