#include <iostream>
#include <memory>

int main()
{
    auto sp = std::make_shared<int>(); //sp is shared_ptr type point to int 0
    auto p = sp.get(); //p is built-in type pointer, point to dynamic memory, but this memory is not allocated through new
    std::cout << "orginal p address value is: " << p  << ", value is: " << *p << std::endl;
    std::cout << "orginal sp address value is: " << sp << ", value is: " << *sp << std::endl;
    std::cout << "sp.use_count(): " << sp.use_count() << std::endl; // 1

    //delete p; // error
    // Deleting a pointer to memory that was not allocated by new, or deleting the same pointer value more than once, is undefined


    {
        auto sp2(sp);
        std::cout << sp2.use_count() << " " << sp.use_count() << std::endl; // 2 2
    }
    std::cout << sp.use_count() << std::endl; //1
}