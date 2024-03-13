#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <vector>
class Screen
{
public:
    typedef std::string::size_type pos;
    Screen() = default; // needed since we have other constructors
    // cursor initialized to 0 by its in-class initializer
    Screen(pos ht, pos wd, char c): height(ht), width(wd), 
                                    contents(ht * wd, c){} // we cab use content(number, char) because this is not in-class initializer,
                                    // in-class intializer only use = form or {} form initialization
    Screen(pos ht, pos wd, pos num_blanks): height(ht), width(wd) {contents = std::string(num_blanks, ' ');}
                                        // same as : height(ht), width(wd), contents(num_blanks, ' ') {}
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(1, c){}                              
    char get() const // get the character at the cursor
        { return contents[cursor];} // implicity inline
    inline char get(pos ht, pos wd) const; // explicitly inline, overloaded member func
    Screen &move(pos r, pos c); // can be made inline later
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    // in-class intializers must use either = form or direct form intialization using {}
    // so in-calss std::string contents(10, 'a') is error
    // should use std::string contents = std::string(10, 'a')
    // or use std::string contents = "aaa"
    std::string contents; // no in-class initializer, will use default constructor or other constructor, if constructor not include contents, it will be initialized to empty string
};
inline Screen& Screen::move(pos r, pos c) // can specify inline on the defination
{
    pos row = r * width; // compute the row location
    cursor = row + c; // move cursor to the column within that row
    return *this; // return this object as lvalue
}
char Screen::get(pos r, pos c) const // declared as inline in the class
{
    pos row =  r * width; //compute row location
    return contents[row + c]; // return character at the given column
}
#endif