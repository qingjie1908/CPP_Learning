#include <iostream>
#include <string>
#include <vector>

void find_n_replace(std::string &s, std::string &oldval, std::string &newval)
{
    auto iter = s.begin(); // scan each char in string s
    
    while(iter!= s.end()){ 
        if(*iter == oldval[0]){// match the first char in old, since last match insert may exceeds current s.size() and move the iter out of current end in previous while loop, need to check
            std::string check_string(iter, iter+oldval.size()); // take same length in s to compare with oldval, not include last element in range
            //if iter+oldval.size() exceeds s.size(), it just copy to the end of s
            if(check_string == oldval){ //match oldval, which also means iter+oldval.size() not exceeds s.size()
                iter = s.erase(iter, iter+oldval.size()); //erase oldval, return iter of element after last erased
                //now insert newval before iter
                iter = s.insert(iter, newval.begin(), newval.end()); // return iter to first inserted element
                //now move iter after newval to further check string in s
                iter = iter + newval.size();
                //after last match, if newval is longer than oldval, iter will be one past of last element in updated inserted s, which is the end() if s
            } else { // first char match check_string but whole does not match oldval
                ++iter;
            }
        } else { //not match first char in oldval
            ++iter;
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