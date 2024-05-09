#include <iostream>
#include <string>
#include <vector>

//==== ex 9.45 ====
std::string fill_name(std::string &name, std::string &prefix, std::string &suffix)
{
    auto iter = name.begin();

    //insert prefix before name using iter
    auto begin_prefix = prefix.begin();
    auto end_prefix = prefix.end();  
    iter = name.insert(iter, begin_prefix, end_prefix); // return iter to the first inserted element
    iter += prefix.size(); // move iter to point to begin of name

    //append suffix after name
    name.append(" " + suffix); // return reference to name

    return name;
}

// ==== ex 9.46 ====
std::string fill_name_pos(std::string &name, std::string &prefix, std::string &suffix)
{
    //insert prefix before name using pos and insert
    decltype(name.size()) pos = 0;
    name.insert(pos, prefix);

    //insert suffix after name using pos and insert
    pos = name.size(); //one past end element
    name.insert(pos, " " + suffix); //name[name.size()] is one past end

    return name;
}


int main()
{
    std::string name = "Bush";
    std::string prefix = "Mr.";
    std::string suffix = "Jr.";

    std::string full_name = fill_name(name, prefix, suffix);

    std::cout << "full_name is: " << full_name << std::endl;
    // full_name is: Mr.Bush Jr.

    name = "Clinton";
    prefix = "Mrs.";
    suffix = "Sr.";
    full_name = fill_name_pos(name, prefix, suffix);
    std::cout << "full_name is: " << full_name << std::endl;
    //full_name is: Mrs.Clinton Sr.
    return 0;
}