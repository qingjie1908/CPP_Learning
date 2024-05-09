#include <iostream>
#include <string>
#include <vector>

void find_n_replace(std::string &s, std::string &oldval, std::string &newval)
{
    decltype(s.size()) index = 0; 
    
    while(index != s.size()){ 
        if(s[index] == oldval[0]){// match the first char in old, since last match insert may exceeds current s.size() and move the iter out of current end in previous while loop, need to check
            std::string check_string = s.substr(index, oldval.size()); // take same length in s and copy to substr check_string to compare with oldval
            //if index + oldval.size() exceeds s.size(), it just copy to the end of s
            if(check_string == oldval){ //match oldval, which also means index + oldval.size() not exceeds s.size()
                s.replace(index, oldval.size(), newval); //erase oldval, replace it with string newval, s now updated
                //now update index
                index = index + newval.size();
            } else { // first char match check_string but whole does not match oldval
                ++index;
            }
        } else { //not match first char in oldval
            ++index;
        } 
    }
}


int main()
{
    std::string s1 = "tht thx to tho thru thrx ewrqthru thru thothru";
    std::string oldval = "tho";
    std::string newval = "though";
    find_n_replace(s1, oldval, newval);
    std::cout << "s1 replacye tho to though are: " << std::endl;
    std::cout << s1 << std::endl;
    //tht thx to though thru thrx ewrqthru thru thoughthru


    oldval = "thru";
    newval = "through";
    find_n_replace(s1, oldval, newval);
    std::cout << "s1 replacye thru to through are: " << std::endl;
    std::cout << s1 << std::endl;
    //tht thx to though through thrx ewrqthrough through thoughthrough

    return 0;
}