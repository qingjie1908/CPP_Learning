#include <iostream>
#include <vector>
#include <memory>

std::vector<int> * func1_crate()
{
    auto p1 = new std::vector<int>(); // p point to dynamic memory hold empty vec int
    std::cout << "p1 value, which is the vec memory address is: " << p1 << std::endl;
    return p1; //its caller func responsible to free the memory
}

// std::vector<int> * func2_read(std::istream &is)
// {
//     auto p2 = func1_crate(); //now p2 point to dynamic memory
//     //after func1_create() finish, p1 out of scope, pointer p1 destroyed, but dynamic memory not, it reference count still has 1 which is p2

//     int i; //hold read vaule from istream
//     while(is >> i){
//         p2->push_back(i);
//     }

//     return p2; //func2's caller func responsible to free the memory
// }

std::vector<int> * func2_read()
{
    auto p2 = func1_crate(); //now p2 point to dynamic memory
    //after func1_create() finish, p1 out of scope, pointer p1 destroyed, but dynamic memory not, it reference count still has 1 which is p2

    std::cout << "p2 value, which is the vec memory address is: " << p2 << std::endl;
    int i = 5; 
    while(i != 0){
        p2->push_back(i);
        --i;
    }

    return p2; //func2's caller func responsible to free the memory
}

void func3_print(std::vector<int> *p3){ //pass p2 to p3 when call func3
    auto iter = p3->begin();
    while(iter != p3->end()){
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;
    std::cout << "p3 value, which is the vec memory address is: " << p3 << std::endl;
    //now free the memory
    delete p3;
}

int main()
{
    //first create a empty vec and read value into it
    //func2 will call func1
    //auto ptr_result = func2_read(std::cin);
    auto ptr_result = func2_read();
    //after func2 call, p2 out of scope, this pointer will be destoyed, now ptr_result hold the vec memory address

    std::cout << "ptr_result value, which is the memory address is: " << ptr_result << std::endl;

    func3_print(ptr_result);
    //after func3(), all pointer point to dynamic memory are invalidated since that memory is freed in func3
    //p1, p2, p3 pointer out of scope are destroyed
    //ptr_result invalid, but it still holds the address to that memory
    std::cout << "ptr_result value, after vec memory freed, is still holding the memory address: " << ptr_result << std::endl; 
    ptr_result = nullptr; //indicates that p is no longer bound to an object
    std::cout << "ptr_result value after bind it to null pointer is: " << ptr_result << std::endl;

    return 0;

    //output
    // p1 value, which is the vec memory address is: 0x13d605f40
    // p2 value, which is the vec memory address is: 0x13d605f40
    // ptr_result value, which is the memory address is: 0x13d605f40
    // 5 4 3 2 1 
    // p3 value, which is the vec memory address is: 0x13d605f40
    // ptr_result value, after vec memory freed, is still holding the memory address: 0x13d605f40
    // ptr_result value after bind it to null pointer is: 0x0

}
