#include <iostream>

template<typename T_ele, unsigned N> constexpr
unsigned my_getsize(const T_ele (&arr) [N]){
    return N;
}

// The constexpr makes this a compile time expression

int main()
{
    int arr1[] = {1,2,3,4,5};
    std::string arr2[3] = {"a", "b", "c"};

    unsigned size1, size2;
    size1 = my_getsize(arr1); //5
    size2 = my_getsize(arr2); //3


    return 0;
}