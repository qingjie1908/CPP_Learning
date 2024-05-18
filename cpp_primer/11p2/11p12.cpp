#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream> //for string stream




int main()
{
    std::string cur_dir = std::filesystem::current_path();
    std::string new_txt = cur_dir + "/11p12.txt";
    std::ofstream f_out;
    f_out.open(new_txt, std::fstream::app);

    std::vector<std::string> vec_s = {"a", "b", "c", "d", "e"};
    for(int i = 0; i < vec_s.size(); ++i){
        f_out << vec_s[i] << " " << i+1 << std::endl;
    }

    f_out.close();

    std::ifstream f_in;
    f_in.open(new_txt);

    std::vector<std::pair<std::string, int>> vec_pair;

    std::string line;
    while(getline(f_in, line)){
        std::stringstream s_stream(line); //s_stream will be destroyed each loop, no need to call clear()
        std::pair<std::string, int> p;
        s_stream >> p.first >> p.second;
        vec_pair.push_back(p);

        //other way to create pair
        //first make_pair(v1, v2) return a pair
        /*
        std::string s; int n;
        s_stream >> s >> n;
        vec_pair.push_back(make_pair(s, n));
        */

        //second declare p, then p(v1, v2);
    }

    f_in.close();

    std::cout << "there are " << vec_pair.size() << " pairs in the vec." << std::endl;

    for(auto item : vec_pair){
        std::cout << item.first << " " << item.second << std::endl;
    }
}