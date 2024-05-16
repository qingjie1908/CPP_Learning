#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main()
{
    std::string cur_dir_path = std::filesystem::current_path(); //"..../10p4"
    std::string new_text_file = cur_dir_path + "/text_10p29.txt";

    std::ofstream f_o(new_text_file, std::ofstream::app); //create text_10p29.txt in current dir and write to it

    //create iterator binding f_o, each tiem write to f_o will also write a space
    std::ostream_iterator<std::string> os_iter(f_o, " ");

    std::vector<std::string> vec_s1 = {"This", "is", "Qingjie", "."};

    //now copy vec_s1 to new text file
    //it's like first os_iter = vec_s1.begin()
    //equals f_o << *os_iter, remember when initialize os_iter we add a " "
    //so it's like f_o << "This" << " "; return os_iter
    //then move to next element in vec_s1
    std::copy(vec_s1.begin(), vec_s1.end(), os_iter);

    //after copy, close f_o
    f_o.close();

    //now read text_file
    std::ifstream f_i(new_text_file);

    //create ierator binding f_i
    std::istream_iterator<std::string> is_iter(f_i);
    std::istream_iterator<std::string> is_eof; //not binding, default initialized to off_the_end iterator for istream

    //store text_file into vec_s2
    std::vector<std::string> vec_s2;
    std::insert_iterator insert_vec(vec_s2, vec_s2.begin()); 

    //first, is_iter = f_i first element
    //then insert_vec = is_iter which call vec_s2.push_back()
    //then ++is_iter, which move to f_i second element,
    //until is_iter hit end of life of new text file
    std::copy(is_iter, is_eof, insert_vec);

    f_i.close();

    //now print the content from vec_s2 to output stream
    //cout_iter binding std::cout with a space " " for each time writing to cout 
    std::ostream_iterator<std::string> cout_iter(std::cout, " ");

    //first cout_iter = vec_s2.begin()
    //equals std::cout << *cout_iter << " ";
    //return cout_iter
    //then next cout_iter = vec_s2 next element iter ...
    std::copy(vec_s2.begin(), vec_s2.end(), cout_iter);

    cout_iter = "\n"; //print newline to std::cout at last

    //output
    /*
    This is Qingjie .

    */

    return 0;
}