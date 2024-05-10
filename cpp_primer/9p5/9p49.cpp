#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
    // command line: ./9p49 test1.txt
    //so argv[0] = 9p49, which is program name
    //argv[1] = test1.txt
    //then argc = 2


    std::string file_name = argv[1]; // test1.txt
    file_name.insert(file_name.begin(), '/'); //  /test1.txt
    std::string file_path;
    file_path = std::filesystem::current_path(); // xxx/xxx/9p5
    file_path.append(file_name); // xxx/xxx/9p5/test1.txt

    std::fstream f1;
    f1.open(file_path, std::fstream::app);

    //write 50 words info file with random length for each word, and each each word contains random char int

    for(int i = 0; i < 50; ++i){
        
        //create random word length btween 1~10;
        int word_length = random()%(10-1+1) + 1;

        //create random word
        std::string word;
        for(int i = 0; i < word_length; ++i){
            //create random char bewtween a-z:
            //for alphabetic char
            // A-Z : 65 - 90
            // a-z : 97 - 122
            int ascii_numer = random()%(122-97+1) + 97;
            char c = static_cast<char> (ascii_numer);
            word.push_back(c);
        }

        f1 << word << " ";
    }

    f1 << std::endl;

    f1.close();

    //define string withd ascender letter
    std::string ascender_letter = "bdfhijklt";
    std::string descender_letter = "gjpqy";
    //std::string normal_letter = "acemnorsuvwxz";

    //reads a file contain random words
    f1.open(file_path);
    std::string check_word;
    std::vector<std::string> want_word; //hold normal letter word, there can be multiple normal word with same size
    while(f1 >> check_word) {
        //check if this check_word contains any char neither ascenders nor descenders
        if(check_word.find_first_of(ascender_letter) == std::string::npos && check_word.find_first_of(descender_letter) == std::string::npos){
            want_word.push_back(check_word);
        }
    }

    f1.close();

    //first find max_size in want_word
    std::string::size_type want_word_max_size = 0;
    for(auto iter = want_word.begin(); iter != want_word.end(); ++iter){
        if(iter->size() > want_word_max_size){
            want_word_max_size = iter->size();
        }
    } 

    //output longest word in want_word vector
    for(auto iter = want_word.begin(); iter != want_word.end(); ++iter){
        if(iter->size() == want_word_max_size) {
            std::cout << "longest word that contains neither ascenders nor descenders are: " << *iter << std::endl;
        }
    }

    return 0;

}