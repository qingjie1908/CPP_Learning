#include <vector>
#include <iostream>

template<typename T>
void print(T& c){
    typedef typename T::size_type sz_t;
    for(sz_t i = 0; i < c.size(); ++i){
        std::cout << c[i] << " ";
    }

    typedef typename T::iterator it_t;
    for(it_t curr = c.begin(); curr != c.end(); ++curr){
        std::cout << *curr << " ";
    }
}

int main()
{
    std::vector<int> vec1 = {1, 3, 4, 5, 6};

    print(vec1);
    std::cout << std::endl; //1 3 4 5 6 1 3 4 5 6
    
}