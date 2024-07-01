#ifndef SCREEN
#define SCREEN

#include <vector>
#include <string>
#include <iostream>

typedef std::string::size_type pos;

template<pos H, pos W>
class Screen
{
friend inline std::ostream& operator<<(std::ostream& os, const Screen& obj){return os << obj.contents;}
//generates a non-template operator<< for this T

//if want to generate a template version operator<<, need to declare before class Screen
friend inline std::istream& operator>>(std::istream& is, Screen& obj){
    std::string read_word;
    is >> read_word;
    obj.contents = obj.contents + read_word;

    obj.height = (obj.contents).size()/ (obj.width);

    if(((obj.contents).size() % (obj.width)) > 0){
        ++obj.height;
    }

    return is;
}

public:
    
    Screen():height(H), width(W), contents(H * W, ' '){} 
    // cursor initialized to 0 by its in-class initializer
    explicit Screen(char c): height(H), width(W), 
                                    contents(H * W, c){} // we cab use content(number, char) because this is not in-class initializer,
                                    // in-class intializer only use = form or {} form initialization
    explicit Screen(pos num_blanks): height(H), width(W) {contents = std::string(num_blanks, ' ');}
                                        // same as : height(ht), width(wd), contents(num_blanks, ' ') {}
    // Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(1, c){}
    Screen &set(char);
    Screen &set(pos, pos, char);                              
    char get() const // get the character at the cursor
        { return contents[cursor];} // implicity inline
    inline char get(pos ht, pos wd) const; // explicitly inline, overloaded member func
    Screen &move(pos r, pos c); // can be made inline later
    // display fucntion overloaded on whether the object is const or not
    // const object can only call const member func
    // non-const object can call both non-const and const member func, but non-const member func is better match
    Screen& display(std::ostream &os)
    {
        do_display(os);
        return *this;
    }
    const Screen& display(std::ostream &os) const // const member func return *this should have a return type this is reference to const
    {
        do_display(os);
        return *this;
    }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    // in-class intializers must use either = form or direct form intialization using {}
    // so in-calss std::string contents(10, 'a') is error
    // should use std::string contents = std::string(10, 'a')
    // or use std::string contents = "aaa"
    std::string contents; // no in-class initializer, will use default constructor or other constructor, if constructor not include contents, it will be initialized to empty string
    // when non-const object call non-const display() then call const do_display(), 'this' pointer will implicitly converted from pointer to non-const to a pointer to const
    void do_display(std::ostream &os) const // functions do the work of displaying a screen, which is read only, not write to the object
    {
        os << contents;
    }
    pos size() const;
};

template<pos H, pos W>
inline Screen<H, W>& Screen<H, W>::move(pos r, pos c) // can specify inline on the defination
{
    pos row = (r-1) * width; // compute the row location
    cursor = row + c - 1; // move cursor to the column within that row
    return *this; // return this object as lvalue
}

template<pos H, pos W>
char Screen<H, W>::get(pos r, pos c) const // declared as inline in the class
{
    pos row =  (r-1) * width; //compute row location
    return contents[row + c - 1]; // return character at the given column
}
template<pos H, pos W>
inline Screen<H, W>& Screen<H, W>::set(char c)
{
    contents[cursor] = c; // set the new value at the current cursor location
    return *this; // return this object as an lvalue
}

template<pos H, pos W>
inline Screen<H, W>& Screen<H, W>::set(pos r, pos col, char ch)
{
    contents[(r-1)*width + col - 1] = ch;
    return *this;
}

template<pos H, pos W>
pos Screen<H, W>::size() const
{
    return height * width;
}


#endif