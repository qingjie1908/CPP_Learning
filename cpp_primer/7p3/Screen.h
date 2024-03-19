#ifndef SCREEN_H
#define SCREEN_H
#include <string>
#include <vector>
// /Users/qingjie/github/CPP_Learning/cpp_primer/7p3/Screen.h
class Screen
{
// Window_mgr members can access the private parts of class Screen
friend class Window_mgr;
public:
    typedef std::string::size_type pos;
    Screen() = default; // needed since we have other constructors
    // cursor initialized to 0 by its in-class initializer
    Screen(pos ht, pos wd, char c): height(ht), width(wd), 
                                    contents(ht * wd, c){} // we cab use content(number, char) because this is not in-class initializer,
                                    // in-class intializer only use = form or {} form initialization
    Screen(pos ht, pos wd, pos num_blanks): height(ht), width(wd) {contents = std::string(num_blanks, ' ');}
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
inline Screen& Screen::set(char c)
{
    contents[cursor] = c; // set the new value at the current cursor location
    return *this; // return this object as an lvalue
}
inline Screen& Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;
    return *this;
}
Screen::pos Screen::size() const
{
    return height * width;
}
/*
// typedef std::string Type;
// Type initVal();
class Exercise {
   public:
       typedef double Type;
       Type setVal(Type);
       Type initVal();
   private:
       int val;
};
Exercise::Type Exercise::setVal(Type parm) {
       val = parm + initVal();
return val; }
*/
#endif