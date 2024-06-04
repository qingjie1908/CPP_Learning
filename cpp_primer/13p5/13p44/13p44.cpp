#include <iostream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p5/13p44/my_string.h"
#include <vector>

int main()
{
    my_string_c m_str1;
    char c1 = m_str1.back();
    char c2 = m_str1.front();
    bool b1 = m_str1.empty(); //true
    char* cp1 = m_str1.begin();
    char* cp2 = m_str1.end(); //cp2 = cp1, hold same adderss value, *cp1 = *cp2 = '\0'
    
    my_string_c m_str2("hello");
    char c3 = m_str2.back(); //'o'
    char c4 = m_str2.front(); //'h'
    bool b2 = m_str2.empty(); //false
    char* cp3 = m_str2.begin(); //"hello", *cp3 = 'h'
    char* cp4 = m_str2.end(); // "", *cp4 = '\0'
    for(char* it = m_str2.begin(); it != m_str2.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //h e l l o

    char c_arr[] = "world";
    my_string_c m_str3(c_arr);
    char c5 = m_str3.back(); //'d'
    char c6 = m_str3.front(); //'w'
    bool b3 = m_str3.empty(); //false
    char* cp5 = m_str3.begin(); // cp5 is "world", *cp5 is 'w'
    char* cp6 = m_str3.end(); //cp6 is "", *cp6 is '\0'
    for(char* it = m_str3.begin(); it != m_str3.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //w o r l d

    my_string_c m_str4(m_str3); //my_string_c copy constructor called
    char c7 = m_str4.back();
    char c8 = m_str4.front();
    bool b4 = m_str4.empty();
    char* cp7 = m_str4.begin();
    char* cp8 = m_str4.end();
    for(char* it = m_str4.begin(); it != m_str4.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //m_str4 contents same as m_str3, just memory address different

    m_str4 = m_str2; //contents change from "world" to "hello"; mp_start, mp_end holding value also change
    //copy assignment operator called
    char c9 = m_str4.back();
    char c10 = m_str4.front();
    bool b5 = m_str4.empty();
    char* cp9 = m_str4.begin();
    char* cp10 = m_str4.end();
    for(char* it = m_str4.begin(); it != m_str4.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //h e l l o

    m_str4.push_back(" happy"); //now is "hello happy"
    char c11 = m_str4.back(); //'y'
    char c12 = m_str4.front(); // 'h'
    bool b6 = m_str4.empty();
    char* cp11 = m_str4.begin(); //'h'
    char* cp12 = m_str4.end(); //'\0'
    for(char* it = m_str4.begin(); it != m_str4.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //h e l l o   h a p p y 

    m_str4.push_back(m_str3);//"hello happyworld"
    char c13 = m_str4.back();//'d'
    char c14 = m_str4.front();//'h'
    bool b7 = m_str4.empty();
    char* cp13 = m_str4.begin();
    char* cp14 = m_str4.end();
    for(char* it = m_str4.begin(); it != m_str4.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //h e l l o   h a p p y w o r l d

    char* find_p = m_str4.find('l');
    if(find_p != m_str4.end()){
        *find_p = 'L';
    }
    for(char* it = m_str4.begin(); it != m_str4.end(); ++it){
        std::cout << *it << " ";
    }
    std::cout << std::endl; //h e L l o   h a p p y w o r l d

    //ex 13.48
    std::vector<my_string_c> vec_my_string;
    vec_my_string.push_back(m_str1); //my_string_c copy constructor called for 1 time, now vec.size() = 1, vec.capacity() = 1
    vec_my_string.push_back(m_str2); //my_string_c copy constructor called for 2 times, now vec.size() = 2, vec.capacity() = 2; resize, so copy 2 times for both 2 elements
    vec_my_string.push_back(m_str3); //my_string_c copy constructor called for 3 times, now vec.size() = 3, vec.capacity() = 4; resize, so copy 3 times for all 3 elements
    vec_my_string.push_back(m_str4); //my_string_c copy constructor called for 1 time, now vec.size() = 4, vec.capacity() = 4; not resize, so only need copy 1 time

    vec_my_string.push_back(m_str1); //my_string_c copy constructor called for 5 times, now vec.size() = 5, vec.capacity() = 8; resize, so copy for all 5 elements
    vec_my_string.push_back(m_str2); //my_string_c copy constructor called for 1 times, now vec.size() = 6, vec.capacity() = 8; not resize, so only need copy 1 times for new added element
    vec_my_string.push_back(m_str3); //my_string_c copy constructor called for 1 times, now vec.size() = 7, vec.capacity() = 8; not resize, so only need copy 1 times for new added element
    vec_my_string.push_back(m_str4); ////my_string_c copy constructor called for 1 times, now vec.size() = 8, vec.capacity() = 8; not resize, so only need copy 1 times for new added element

    //move constructor ex 13.49
    my_string_c m_str5(std::move(m_str2)); //be sure not use m_str2 anymore
    //now m_str2.mp_start/end = 0x00000; m_str5 hold memory address of orignal m_str2 pointed to memory 
    //vec_my_string not affected, since its copy constructor, it hold another memory, just contents same as m_str2

    //move assignment operator
    m_str5 = std::move(m_str4); //be sure not use m_str4 anymore
    //now m_str4.mp_start/end is nullptr

    return 0;
}