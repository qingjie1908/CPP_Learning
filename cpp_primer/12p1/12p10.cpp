#include <iostream>
#include <vector>
#include <memory>

void process(std::shared_ptr<int> ptr)
{
    std::cout << "ptr.use_count() = " << ptr.use_count() << std::endl;
    //if use process(std::shared_ptr<int>(p)); to call, use_count = 2, one is ptr in this func, one is p in main
    //if use process(std::shared_ptr<int>(p.get())); use_count = 1, independent from p, after this func finished, reference count = 0, memory freed, any access to p is disater, p is dangling pointer 
    std::cout << "ptr value is: " << ptr << " , point to " << *ptr; //0x13ee05e70, 42
    *ptr = 11;
}

int main()
{
    //====== why we should not use get to initialize or assgn another smart pointer ====
    //std::shared_ptr<int> p = new int(42); //wrong build in ptr cannot converted to shared_ptr
    //should use direct initialize form if want to use new to initialize
    std::shared_ptr<int> p(new int(42));
    std::cout << "p value is: " << p << " ,point to " << *p << std::endl; //0x13ee05e70, 42
    std::cout << "p.use_count = " << p.use_count() << std::endl; // 1

    int *q = p.get();
    std::cout << "q value is: " << q << " ,ponit to " << *q << std::endl; //0x13ee05e70, 42
    
    //use get to initialze or assgn smart pointer is disaster see below from line 25 to line 39
    //auto temp = std::shared_ptr<int>(q); disaster, same like below
    //auto temp = std::shared_ptr<int>(p.get()); //disaster, use two independent share_ptr point to the same memory
    //std::cout << "temp value is: " << temp << " ,point to " << *temp << std::endl; //0x13ee05e70, 42
    //std::cout << "temp.use_count = " << temp.use_count() << std::endl;// 1, not 2!!!

    //this is disaster,
    //temp and p point to same memory
    //but they are independent since .use_count() is 1
    //so when go out of main scope, both p and temp use count will from 1 to 0
    //when p destroyed, it will do delete p, memory freed
    //when temp destoryed, it will do delete temp
    //the second one delete the same memory twice, which is undefined
    

    //==== ex 12.10 ====
    process(std::shared_ptr<int>(p)); //it like temp = std::shared_ptr<int>(p), then ptr = temp
    //in process(), use_count = 2, since ptr also point to this object
    //after process call, ptr destoyed, reference count change to 1
    std::cout << "p value is: " << p << " ,point to " << *p << std::endl; //0x13ee05e70, 11
    std::cout << "p.use_count = " << p.use_count() << std::endl; // 1

    //process(std::shared_ptr<int>(p.get())); // disaster, the ptr in the func will refecence count = 1 not 2
    //when process finished, ptr in process() destroyed, reference count to 0, then memory freed
    //after main, p out of scope, p destroyed, p.use_count = 0, delete p, the memory freed will be deleted again, disaster
    

    return 0;

}