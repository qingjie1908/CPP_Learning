#include <map>
#include <iostream>
#include <vector>
#include <list>

int main()
{
    std::map<std::vector<int>::iterator, int> map1;
    std::vector<int> vec_i1(10);
    std::vector<int> vec_i2(10,5);
    std::vector<int> vec_i3(10, 6);

    map1[vec_i1.begin()] = 1;
    map1[vec_i2.begin()] = 2;
    map1[vec_i3.begin()] = 3;

    for(auto vec : {vec_i1, vec_i2, vec_i3}){
        for (auto item : vec){
            std::cout << item << " ";
        }
        std::cout << std::endl;
    }
    /*
    0 0 0 0 0 0 0 0 0 0 
    5 5 5 5 5 5 5 5 5 5 
    6 6 6 6 6 6 6 6 6 6 
    */

    /*
    std::map<std::list<int>::iterator, int> map2;
    std::list<int> lst1 = {1, 3, 5, 7, 9};
    std::list<int> lst2 = {1, 2};

    //wrong for map2,
    //since key type must have strict weak ordering,
    //which means we need to compare the key type
    //while in vector, iter can be compared
    //in list, iter is not arithmetic, cannot be compared
    map2[lst1.begin()] = 1;
    map2[lst2.begin()] = 2;

    for(auto item : map2){
        std::cout << *(item.first) << std::endl;
    }
    */
   return 0;
  
}