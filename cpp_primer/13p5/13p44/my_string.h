#ifndef MYSTRING
#define MYSTRING

#include <memory>

class my_string_c{
friend std::ostream& operator<<(std::ostream& os, const my_string_c& obj);
friend bool operator==(const my_string_c& lhs, const my_string_c& rhs);
friend bool operator!=(const my_string_c& lhs, const my_string_c& rhs);
friend bool operator<(const my_string_c& lhs, const my_string_c& rhs);
public:
    my_string_c(); //default constructor
    my_string_c(const char* cp); //string literal is transferred to const char* 
    //copy constructor
    my_string_c(const my_string_c& orig);
    //copy assignment operator
    my_string_c& operator=(const my_string_c& rhs);
    //destructor
    ~my_string_c();

    //move constructor
    my_string_c(my_string_c&& orig);

    //move assignment operator
    my_string_c& operator=(my_string_c&& rhs);

    char& operator[](size_t n);
    const char& operator[](size_t n) const;

    bool empty() const {return mp_start == mp_end;} //note: null_ptr = null_ptr; nullptr cannot compare with char*;
    unsigned int size() const {return mp_end - mp_start;} //not include the last '\0'; nullptr - nullptr = 0
    char* begin() const {return mp_start;};
    char* end() const {return mp_end;} //point to '\0', note '\0' != nullptr, can dereference *p to '\0', cannot dereference nullptr
    char* find(const char a); //return first pointer hold same as char a, else return this.end()
    char back(); //return last char, value copy
    char front(); //return first char, value copy
    void push_back(const char* new_obj); //push_back("string literal")
    void push_back(const my_string_c& new_obj); //push_back(my_string_c obj)
    //char* erase(char* ele); //erase some char in my_string_c, return pointer after this erased ele
    //for my_string_c, erase need only invalidate iter after this erased ele



private:
    char* mp_start; //pointer to point to first element in a char[]
    //'\0; is null character, it's not nullptr; it's also an object with type char
    char* mp_end; //pointer to off the end in char[], which point to '\0'

    static std::allocator<char> alloc; //this is decalartion only, implementation in another implementation cpp file

    void free(); //free the memory


};

bool operator==(const my_string_c& lhs, const my_string_c& rhs);
bool operator!=(const my_string_c& lhs, const my_string_c& rhs);
bool operator<(const my_string_c& lhs, const my_string_c& rhs);
#endif

