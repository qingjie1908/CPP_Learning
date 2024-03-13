#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/7p3/Screen.h"
#include <string>
#include <vector>
class Window_mgr
{
public:
    
private:
    // Screens this Window_mgr is tracking
    // by default, a Window_mgr has one standard sized blank Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};

};
#endif