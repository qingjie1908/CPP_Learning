#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

int main()
{
    //==== ex 10.3 ====
    std::vector<int> vec_i = {3, 4, 5, 6, 7};
    //accumulate is in numeric header
    auto result_1 =  std::accumulate(vec_i.begin(), vec_i.end(), 0);
    std::cout << "0 + sum of vector int {3,4,5,6,7} are: " << result_1 << std::endl;

    //==== ex 10.4 ====
    std::vector<double> vec_d = {3.1, 4.2, 5.3, 6.4, 7.5};
    auto result_2 =  std::accumulate(vec_d.begin(), vec_d.end(), 0); //3 + 4 + 5 + 6 + 7 + 0 = 25
    auto result_3 =  std::accumulate(vec_d.begin(), vec_d.end(), 0.0); //3.1 + 4.2 + 5.3 +6.4 +7.5 +0.0 = 26.5
    std::cout << "0 + sum of vector double {3.1, 4.2, 5.3, 6.4, 7.5} are: " <<result_2 << std::endl;
    std::cout << "0.0 + sum of vector double {3.1, 4.2, 5.3, 6.4, 7.5} are: " <<result_3 << std::endl;

    //==== ex 10.5 ====
    std::vector<const char*> vec_c_str_1 = {"ab", "aa", "ba", "c"};
    std::vector<const char*> vec_c_str_2 = {"ab", "aa", "ba", "c", "cc"};

    auto result_4 = std::equal(vec_c_str_1.begin(), vec_c_str_2.end(), vec_c_str_2.begin());
    std::cout << result_4 << std::endl; //0
    /*
    std::cout << *vec_c_str_1.begin() << std::endl; //ab

    auto iter = vec_c_str_1.begin();
    std::cout << *iter << std::endl; //ab
    std::cout << **iter << std::endl; //a
    */

    /* aaa_p is just like iter
    char aaa[] = "ab";
    char (*aaa_p)[] = &aaa;
    std::cout << *aaa_p << " " << *(*aaa_p+1) << std::endl; //ab , b
    */
   std::vector<std::string> vec_str_1 = {"ab", "aa", "ba", "c"};
   auto result_5 = std::equal(vec_str_1.begin(), vec_str_1.end(), vec_c_str_2.begin());
   std::cout << result_5 << std::endl; //1

   const char *a1 = "ab";
   const char *a2 = "ab";
   auto *iter1 = &a1;
   auto *iter2 = &a2;

   // std::cout << (a1==a2) << std::endl; //compare two pointers which is undefinded
}