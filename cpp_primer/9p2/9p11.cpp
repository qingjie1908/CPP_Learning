#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <array>

int main()
{
    //===Ex 9.11, 9.12

    // vec default constructor, empty
    std::vector<int> i_vec1;

    // C c{a,b,c...}
    std::vector<int> i_vec2 {2, 4, 5, 6};

    //C c={a,b,c...}
    std::vector<int> i_vec3 = {1, 3, 5};
    i_vec3 = i_vec2;
    std::cout << "i_vec3 are:" << std::endl; // 2 4 5 6
    for (auto item : i_vec3){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    i_vec3 = {1, 3, 5};
    i_vec2 = i_vec3;
    std::cout << "i_vec2 are:" << std::endl; // 1 3 5
    for (auto item : i_vec2){
        std::cout << item << " ";
    }
    std::cout << std::endl;


    //C c1(c2)
    std::vector<int> i_vec4(i_vec2);

    //C c1 = c2
    std::vector<int> i_vec5 = i_vec3;

    //C c(b, e)
    std::vector<int>::iterator begin = i_vec2.begin();
    auto end = i_vec2.end();
    decltype(i_vec2.begin()) mid = end - 2; // mid now point to 3
    std::vector<int> i_vec6(begin, mid); //{1}, not inlcude mid
    std::cout << "i_vec6 are:" << std::endl;
    for (auto item : i_vec6){
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    //C seq(n)
    std::vector<int> i_vec7(5);
    std::cout << "i_vec7 are:" << std::endl;
    for (auto item : i_vec7){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //C seq(n,t)
    std::vector<int> i_vec8(4, 1);
    std::cout << "i_vec8 are:" << std::endl;
    for (auto item : i_vec8){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    //=== Ex 9.12
    std::list<int> lst1 = {3, 5, 7};
    std::vector<int> i_vec9 = {4, 6};

    auto begin9 = i_vec9.begin();
    auto end9 = i_vec9.end();
    // d_vec1 = i_vec9 not allowed since int and double are different type
    std::vector<double> d_vec1(begin9, end9); 
    std::cout << "d_vec1 are:" << std::endl;
    for (auto item : d_vec1){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    auto beginlist = lst1.begin();
    auto endlist = lst1.end();
    std::vector<double> d_vec2(beginlist, endlist);
    std::cout << "d_vec2 are:" << std::endl;
    for (auto item : d_vec2){
        std::cout << item << " ";
    }
    std::cout << std::endl;

    return 0;
}