#include <memory>
#include <string>
#include <iostream>

char* concat_cstr(char* a1, char* a2) //when pass char [], convert to pointer
{
    //first get length of a1, a2, strlen() not include the null terminator
    auto large_len = strlen(a1) + strlen(a2);

    //use large_len to create new array stored a1 + a2, note large_len need to + 1, 1 for null terminator space
    char* p_large_cstr = new char[large_len+1];

    //p_large_cstr is built-in pointer, can use subscript
    size_t i = 0;

    //first traverse a1 then write into p_large_cstr
    for(size_t pos_a1 = 0; pos_a1 < strlen(a1); ++pos_a1){
        //not strlen() return size not contain null; so last subscript should be a1[strlen(a1) - 1]
        //p_large_cstr[i] is like *(p + i), get a char in array
        //a1[pos_a1] is like *(a1+pos_a1), char in char a1[]
        p_large_cstr[i] = a1[pos_a1];
        ++i;
    }
    //now i = strlen(a1);
    // and p_large_cstr[i] is null , ready for input from a2
    //after this, traverse a2, then write into p_large_cstr remaining part

    for(size_t pos_a2 = 0; pos_a2 < strlen(a2); ++pos_a2){
        //continue i
        p_large_cstr[i] = a2[pos_a2];
        ++i;
    }

    //after traverse a1 and a2, now i = 0 + strlen(a1) + strlen(a2) = large_len
    //p_large_str[i] point to last element, this should be null terminator
    p_large_cstr[i] = '\0'; 


    return p_large_cstr; //note it point to dynamic array, and is built-in pointer, caller is resposeble to delete
}

std::string* concat_stdstr(std::string &s1, std::string &s2)
{
    auto p_stdstr = new std::string(s1+s2);

    return p_stdstr; //return built-in pointer to dynamic memory
    //caller responsible for free memory
}

int main()
{
    //string literals are c-style string
    char a1[] = "cstring1";
    char a2[] = "cstring2";

    //a program to concatenate two strings

    auto p_result = concat_cstr(a1, a2);

    //now first print p_result
    std::cout << *p_result << std::endl; //c
    std::cout << p_result << std::endl; //cstring1cstring2

    //then delete it, since it point to a dynamic memory initialized from new, and is a built-in pointer
    //and since it point to array,  [] is necessary
    delete [] p_result;

    //==== use std::string ====
    std::string s_a1 = a1;
    std::string s_a2 = a2;

    auto p_result_2 = concat_stdstr(s_a1, s_a2);

    std::cout << *p_result_2 << std::endl; //cstring1cstring2

    //now free p_result_2, since p_result_2 is not array, not need delete []
    delete p_result_2; 

    return 0;

}