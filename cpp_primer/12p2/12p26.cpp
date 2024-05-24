#include <string>
#include <memory>
#include <iostream>

int main()
{
    int n = 20;

    //first create a allocator object
    std::allocator<std::string> alloc;

    //then allocate n string memory
    auto p_start = alloc.allocate(n); //these memory are not constructed yet

    //p_start point to first un-consturcted memory part for first string
    auto p_traverse = p_start;

    std::string s; //read from cin
    while(std::cin >> s && (p_traverse - p_start) != n){
        //(p_traverse - p_start) != n make sure p_travers not point the off the end of the unconstruted memory
        //p_start+n is the off end pos
        //alloc.construct and destroy member has deprecated in c++20


        //instead using static member in allocator_traits
        //void std::allocator_traits<Alloc>::construct( Alloc& a, T* p, Args&&... args)
        std::allocator_traits<std::allocator<std::string>>::construct(alloc, p_traverse, s);
        ++p_traverse; //move to next unconstructed memory
    }

    //now p_travers point to one past the last initilized memory
    //print these string in the constructed memory
    auto p = p_start;
    while(p != p_traverse){
        std::cout << *p << " ";
        ++p;
    }
    std::cout << std::endl;

    //now destroy the object in the actually constructed memory
    //now p point to one past last initialized memory, = p_traverse
    p = p_start; //reset p to start
    while(p != p_traverse){
        std::allocator_traits<std::allocator<std::string>>::destroy(alloc, p);
        ++p;
    }
    
    //now deallocate memory
    alloc.deallocate(p_start, n);

    //input: a b c d e
    //output: a b c d e

    //input: a b c d e f g h i j k l m n o p q r s t u (u is 21st element, larger than n)
    //output: a b c d e f g h i j k l m n o p q r s t 

    return 0;
}