#include <iterator>
#include <iostream>

/* 
//below call my_begin(arr1) is wrong
//cuase compiler use argument type to dedulce tempelate parameter type
//so it can only deduce T_ele to int [5]; but does not know T_iter,

template<typename T_iter, typename T_ele>
T_iter my_begin(const T_ele (&arr)){
    return arr[0];
}
int arr1[5] = {1,2,3,4,5};
auto iter1 = my_begin(arr1);//wr

*/

/*
template<typename T_ele>
T_ele* my_begin(T_ele* arr) {
    return arr;
}

hard to get end
*/


template<typename T_ele, unsigned N>
T_ele* my_begin(T_ele (&arr) [N]){
    return &arr[0];
}
//if  T_ele* my_begin(const T_ele (&arr) [N]); error, cannot initialize return obj of tyoe int* with rvalue type 'const int *'
//cause we could use return (type int*) to change the orignal const int, so remove const here
//or we can define const T_ele* my_cbegin(const T_ele (&arr) [N])

template<typename T_ele, unsigned N>
const T_ele* my_cbegin(const T_ele (&arr) [N]){
    return &arr[0];
}

template<typename T_ele, unsigned N>
T_ele* my_end(T_ele (&arr) [N]){
    return (&arr[0] + N);
}

template<typename T_ele, unsigned N>
const T_ele* my_cend(const T_ele (&arr) [N]){
    return (&arr[0] + N);
}




int main()
{
    int arr1[5] = {1, 2, 3, 4, 5};
    auto iter = std::begin(arr1); //need head iterator
    std::cout << *iter << std::endl; //1

    auto iter_begin = my_begin(arr1); //when pass arr1, compiler deducle T_ele to int and N to 5;
    auto iter_end = my_end(arr1);
    for(auto curr = iter_begin; curr != iter_end; ++curr){
        std::cout << *curr << std::endl;
    }
    //1 2 3 4 5

    auto iter_cbegin = my_cbegin(arr1); //here iter_cbegin point to const int, cannot assign to it
}