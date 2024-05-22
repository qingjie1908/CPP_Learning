#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<int>> func1_crate() // return std::shared_ptr
{
    std::shared_ptr p1 = std::make_shared<std::vector<int>>(); // shared ptr p point to dynamic memory hold empty vec int
    std::cout << "p1 value, which is the vec memory address is: " << p1 << std::endl;
    std::cout << "p1.use_count() is: " << p1.use_count() << std::endl; //1, vec memory now only has one user p1
    return p1; //after this call, p1 will be out of scope, vec memory reference count - 1
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

std::shared_ptr<std::vector<int>> func2_read() //return shared ptr
{
    auto p2 = func1_crate(); //now p2 point to dynamic memory vec
    //after func1_create() finish, p1 out of scope, pointer p1 destroyed, memory reference count -1; but dynamic memory not, it reference count still has 1 which is p2

    std::cout << "p2 value, which is the vec memory address is: " << p2 << std::endl;
    std::cout << "p2.use_count() is: " << p2.use_count() << std::endl; //1, p1 destroyed, memory only has one user p2
    int i = 5; 
    while(i != 0){
        p2->push_back(i);
        --i;
    }

    return p2; ////after this call, p2 will be out of scope, destroyed, vec memory reference count - 1
}

void func3_print(std::shared_ptr<std::vector<int>> p3){ //pass p2 to p3 when call func3
    auto iter = p3->begin();
    while(iter != p3->end()){
        std::cout << *iter << " ";
        ++iter;
    }
    std::cout << std::endl;
    std::cout << "p3 value, which is the vec memory address is: " << p3 << std::endl;
    std::cout << "p3.use_count() is: " << p3.use_count() << std::endl; //2, vec_memory has both p3 and ptr_result user now
    //now free the memory
    //delete p3; delete memory not allocated by new, in this case it's allocated by shared_ptr, will be undefined
    //after this call p3, destroyed, out of scope
}

int main()
{
    //first create a empty vec and read value into it
    //func2 will call func1
    //auto ptr_result = func2_read(std::cin);
    auto ptr_result = func2_read();
    //after func2 call, p2 out of scope, this pointer will be destoyed, now ptr_result hold the vec memory address

    std::cout << "ptr_result value, which is the memory address is: " << ptr_result << std::endl;
    std::cout << "ptr_value.use_count() is: " << ptr_result.use_count() << std::endl; //1

    func3_print(ptr_result);
    //after func3(),
    //p1, p2, p3 pointer out of scope are destroyed
    //ptr_result still holds point to that memory
    std::cout << "ptr_result value, holding the memory address: " << ptr_result << std::endl; 
   
    std::cout << "ptr_value.use_count() is: " << ptr_result.use_count() << std::endl; //1, p3 has been destroyed

    //==== ex 12.8 ====
    auto pp = nullptr;
    bool a, b;
    a = static_cast<bool> (pp);
    std::cout << a << std::endl; //0

    if(ptr_result){ //true, it still hold vec memory address
        std::cout << "ptr is not nullptr." << std::endl;
    }

    return 0;

    //after exit main, ptr_result out of scope, destroyed, now vec memory hold reference count = 0; it will be freed automatically since it's handle in shared_ptr class

    //output
    // p1 value, which is the vec memory address is: 0x158605f58
    // p1.use_count() is: 1
    // p2 value, which is the vec memory address is: 0x158605f58
    // p2.use_count() is: 1
    // ptr_result value, which is the memory address is: 0x158605f58
    // ptr_value.use_count() is: 1
    // 5 4 3 2 1 
    // p3 value, which is the vec memory address is: 0x158605f58
    // p3.use_count() is: 2
    // ptr_result value, holding the memory address: 0x158605f58
    // ptr_value.use_count() is: 1
    // ptr is not nullptr.

}
