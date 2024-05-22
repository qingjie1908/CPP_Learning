#include <iostream>
#include <memory>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "ptr.use_count() = " << ptr.use_count() << std::endl;
    //if use process(std::shared_ptr<int>(sp)); to call, use_count = 2, one is ptr in this func, one is sp in main
    //if use process(std::shared_ptr<int>(sp.get())) or (p); use_count = 1, independent from sp, after this func finished, reference count = 0, memory freed, any access to sp is disater, sp is dangling pointer 
    std::cout << "ptr value is: " << ptr << " , point to " << *ptr << std::endl; //0x13ee05e70, 0
    *ptr = 11;
}

int main()
{
    auto p = new int(); // p is built in pointer, point to default value initialized() int 0, 
    auto sp = std::make_shared<int>(); //sp is smart pointer, point to another int 0, different dynamic memroy
    std::cout << "orginal p address value is: " << p << std::endl;
    std::cout << "orginal sp address value is: " << sp << std::endl;

    process(sp); //legall, in func(), use count = 2, after func, use count = 1
    std::cout << "sp.use_count():  " << sp.use_count() << ", *sp is: " << *sp << std::endl;
    
    //process(new int()); // illegal, shared_ptr = built-in ptr, type mismatch, same error for process(p)

    process(std::shared_ptr<int>(p)); //legal, but ptr.refence count = 1, after func, ptr destroyed, refence count =0,  then that memory freed, like delete p
    std::cout << "p, *p: " << p << " " << *p << std::endl; //now p is dangling pointer, only hold address, value is 0(undefined)


}  