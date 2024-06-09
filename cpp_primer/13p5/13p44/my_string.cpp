//implementation of my_string class

#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/13p44/my_string.h"
#include <iostream>

std::allocator<char> my_string_c::alloc; //this is defination; defination only happens once, no need add static since it's in decalaration in header file
//this defination define allocator object named "alloc" that can allocate memory for objects of type char 

//default constructor
my_string_c::my_string_c(){
    //note nullptr and char* are different type
    //'\0' us a null character, it's still and object, type char
    char* p  = alloc.allocate(1);
    std::allocator_traits<decltype(alloc)>::construct(alloc, p, '\0');
    //we can de-reference p; *p = '\0'; but we cannot de-reference nullptr

    mp_start = mp_end = p;
    //after scope, pointer p destroyed, but mp_start/end still hold value of p, which is the dynamic memory of char '\0'
}


//constructor take a char [] or literal std::string
my_string_c::my_string_c(const char* cp){
    //char arr[] = "hello", then its char arr[6], arr[5] = '\0'; strlen(arr) = 5, not include '\0'
    //char* p = "hello" is warning, literal string "hello"; should be const char*
    //strlen func need to include string header
    //now arr is "hello", address like 0x1, *arr = 'h'
    //if arr+1;
    //now arr is "ello", address like 0x2; *arr = 'e'

    //first calculate size, which is not include '\0'
    int n = 0;
    while(*cp != '\0'){
        ++n;
        ++cp;
    }

    //at last n = 5, current cp point to '\0'

    //but when we allocate memory, we should also allocate for '\0'
    char* p = alloc.allocate(n+1);

    mp_start = p;
    mp_end = p + n; //point to '\0'

    char* begin = mp_start;
    cp = cp - n; //now cp back to point to first char

    while(begin != mp_end){
        *begin = *cp;
        ++begin;
        ++cp;
    }
    //now begin = mp_end;
    *begin = '\0';

    //note when out of scope, built-in pointer p,begin destroyed, but mp_start/end still hold value of dynamic memory address 

}

//copy cosntructor
my_string_c::my_string_c(const my_string_c& orig){
    //note below code also consider orig is "";
    //so orig.size() = 0; *orig.mp_start = '\0';
    mp_start = alloc.allocate(orig.size() + 1); //+1 is the char '\0'
    mp_end = mp_start + orig.size();
    char* curr = mp_start;
    char* orig_start = orig.begin();
    while(curr != mp_end){ //if orig is ""; this loop not executed
        *(curr++) = *(orig_start++); //use current value, then ++
    }
    //now curr = mp_end;
    *mp_end = '\0';

    //ex 13.47
    std::cout << "my_string_c copy constructor called" << std::endl;
}

//destructor
void my_string_c::free(){
    //first destroy each char

    char* curr = mp_end;
    while(curr != mp_start){
        std::allocator_traits<decltype(alloc)>::destroy(alloc, (curr--)); //*mp_end = '\0',is a char object, also need destroy
    }
    //last curr = mp_start, still need to destory
    std::allocator_traits<decltype(alloc)>::destroy(alloc, curr);

    //de-allocated memory
    alloc.deallocate(mp_start, size()+1);

}

my_string_c::~my_string_c(){
    free();
}

//copy assignment operator
my_string_c& my_string_c::operator=(const my_string_c& rhs){
    char* new_start = alloc.allocate(rhs.size() + 1); //+1 for '\0'
    
    //copy rhs contents to new memory
    char* curr = new_start;
    char* curr_rhs = rhs.begin();

    while(curr_rhs != rhs.end()){ //rhs.end() is '\0'
        *(curr++) = *(curr_rhs++);
    }
    //curr now is new_end
    *curr = '\0';

    //free lhs "this" orginal memory
    free();

    //update "this" to new memory
    mp_start = new_start;
    mp_end = curr;

    //ex 13.47
    std::cout << "copy assignment operator called" << std::endl;

    return *this;
}

//move constructor
my_string_c::my_string_c(my_string_c&& orig){
    mp_start = orig.mp_start;
    mp_end = orig.mp_end;

    //now update orig pointer to nullptr
    //otherwise when orig out of scope in user code, the dynamic memory pointed by 'this' will also be free
    orig.mp_start = orig.mp_end = nullptr;

    std::cout << "move constructor called" << std::endl;
}

//move assignment operator
my_string_c& my_string_c::operator=(my_string_c&& rhs){
    //check self assignment
    if(this != &rhs){ //not the same obj
        //first need to free "this" obj
        free();

        //now update 'this' to point to rhs hold memory
        mp_start = rhs.mp_start;
        mp_end = rhs.mp_end;

        rhs.mp_start = rhs.mp_end = nullptr;
    }

    //else lhs = rhs. do nothing
    std::cout << "move assignment operator called" << std::endl;

    return *this;
}

char my_string_c::back(){
    if(!empty()){
        //char temp = *(--mp_end); //make sure mp_end not change, --end is wrong
        char temp = *(end()-1);
        return temp; //this will use char own copy constructor
    } else{
        return '\0';
    }  
}

char my_string_c::front(){
    return *begin(); //if is empty, then it's return '\0'
}

char* my_string_c::find(const char a){ //return first pointer hold same as char a
    char* curr = mp_start;
    while(curr != mp_end){
        if(*curr == a){
            return curr;
        } else {
            ++curr;
        }
    }
    //if not find match, now curr = mp_end
    return mp_end;
}

void my_string_c::push_back(const char* add_obj){
    // this version use obj.push_bach("string_literal")
    //first check add_obj size
    int n = 0;
    const char* curr = add_obj;
    while(*curr != '\0'){
        ++curr;
        ++n;
    }
    //now size is n; new need memory is n + 1; 1 for '\0'

    //allocate new memory for this.size() + add_obj.size() + 1
    char* new_start = alloc.allocate(size() + n + 1);
    char* curr_new = new_start;

    //copy "this" into new_memory, [mp_start, mp_end)
    std::uninitialized_copy(mp_start, mp_end, curr_new);

    //copy add_obj into following new_memory
    curr_new += size();
    std::uninitialized_copy(add_obj, (add_obj+n), curr_new);

    //construct last memory in new memory to '\0'
    curr_new += n;
    *curr_new = '\0';

    //free "this" old memory
    free();

    //update "this" to new memory
    mp_start = new_start;
    mp_end = curr_new;
}

void my_string_c::push_back(const my_string_c& add_obj){
    //this version use obj.push_bakc(my_string_c_class_obj)

    //we dont need to calculate add_obj size, since we can call add_obj.size()
    //allocate new memory for this.size() + add_obj.size() + 1
    char* new_start = alloc.allocate(size() + add_obj.size() +1);
    char* curr_new = new_start;

    //copy "this into new_memory first part", [this.mp_start, this.mp_end) 
    std::uninitialized_copy(begin(), end(), curr_new);

    //copy add_obj into new_memory second part, [add_obj.mp_start, add_obj.mp_end)
    curr_new += size();
    std::uninitialized_copy(add_obj.begin(), add_obj.end(), curr_new);

    //construct last memory in new memory to '\0'
    curr_new += add_obj.size();
    *curr_new = '\0';

    //free "this" old memory
    free();

    //update "this" to new memory
    mp_start = new_start;
    mp_end = curr_new;
}

//output operator
std::ostream& operator<<(std::ostream& os, const my_string_c& obj){
    char* curr = obj.begin();
    while (curr != obj.end()){
        os << *curr;
        ++curr;
    }
    return os;
}

bool operator==(const my_string_c& lhs, const my_string_c& rhs){
    if(lhs.size() != rhs.size()){
        return false;
    }
    //has same size, compare each element
    char* curr_left = lhs.begin();
    char* curr_right = rhs.begin();
    while(curr_left != lhs.end()){
        if(*curr_left != *curr_right){ //use std::char !=
            return false;
        }
        // left char == right char, continue
        ++curr_left;
        ++curr_right;
    }
    //compare each char, no return false, all equal
    return true;
}
bool operator!=(const my_string_c& lhs, const my_string_c& rhs){
    return !(lhs == rhs);
}
bool operator<(const my_string_c& lhs, const my_string_c& rhs){
    if(lhs.size() < rhs.size()){
        return true;
    }
    if(lhs.size() > rhs.size()){
        return false;
    }
    //size equal, compare each char
    char* curr_left = lhs.begin();
    char* curr_right = rhs.begin();
    while(curr_left != lhs.end()){
        if(*curr_left < *curr_right){ //first encounter left char < right char, not care remaining part
            return true;
        }
        if(*curr_right < *curr_left){ //first encounter left char > right char, not care remaining part
            return false;
        }
        ++curr_left;
        ++curr_right;
    }
    //while loop finished, no return, then all char equal
    return false;
}
