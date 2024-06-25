#include <iostream>
#include <string>

template<typename T_ele>
void print(const T_ele (&arr), const unsigned int& sz){
    for(unsigned int i = 0; i < sz; ++i){
        if(i < sizeof(arr)/sizeof(arr[0])){
            //sizeof(arr) get you the total number of bytes allocated for that array
            //in order to get how many elements, use sizeof(arr)/sizeof(arr[0])
            std::cout << arr[i] << " ";
        }
    }
}


int main()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    print(arr1, 6); // 1 2 3 4 5
    std::cout << std::endl;
    //here T_ele is transferred to int [5]
    //note array size is also part of array type, int [5] and int [6] is different type
    //so if template void print(const T_ele (&arr) [], const unsigned int& sz), 
    //it will be error, T_ele will be transferred to int, int [] and int [5] are different type
    
    print(arr1, 3);
    std::cout << std::endl; // 1 2 3

    std::string arr2[5] = {"aa", "bb", "cc", "dd"};

    print(arr2, 6); //aa bb cc dd 
    std::cout << std::endl;

    print(arr2, 3); //aa bb cc 
    std::cout << std::endl;

    return 0;
}