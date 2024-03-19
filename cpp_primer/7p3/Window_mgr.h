#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/7p3/Screen.h"
#include <string>
#include <vector>
// /Users/qingjie/github/CPP_Learning/cpp_primer/7p3/Window_mgr.h
class Window_mgr
{
public:
    // location ID for each screen on the window
    using ScreenIndex = std::vector<Screen>::size_type;
    // add a Screen to the window and returns its index
    ScreenIndex addScreen(const Screen&);
    // reset the Screen at the given position in screens to all blanks
    void clear(ScreenIndex);
private:
    // Screens this Window_mgr is tracking
    // by default, a Window_mgr has one standard sized blank Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};

};
void Window_mgr::clear(ScreenIndex i)
{
    // s is a reference to the Screen we want to clear
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}
// because the return type appears before the name of the class is seen
// outside class member funtion's return type is outside of class scope, need to add class scope before return type
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}
#endif