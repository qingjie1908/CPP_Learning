#include <iostream>
#include <vector>
#include <memory>

int main()
{
    int *q = new int(42), *r = new int(100);
    std::cout << "q point int 42_object1, q value is: " << q << " , *q is: " << *q << std::endl; //0x149605e70, 42
    std::cout << "r point int 100_object2, r value is: " << r << " , *r is: " << *r << std::endl; // 0x149605fc0, 100

    auto backup = r; //remember obj2 address in order to free it after 
    r = q; //now both r and q point to 42_object1, 100_obj2 memory not freed yet
    std::cout << "q point int 42_object1, q value is: " << q << " , *q is: " << *q << std::endl; //0x149605e70, 42
    std::cout << "r now point int 42_object1, r value is: " << r << " , *r is: " << *r << std::endl;; //0x149605e70, 42

    auto q2 = std::make_shared<int>(42), r2 = std::make_shared<int>(100);
    //now q2 point to 42_obj3, r2 point to 100_obj4, they are shared ptr
    std::cout << "q2 is shared_ptr, hold 42_obj3 address: " << q2 << " , *q2 is: " << *q2 << std::endl; //0x149605f58, 42
    std::cout << "q2.use_count() : " << q2.use_count() << std::endl; //1, obj3 only has 1 user

    std::cout << "r2 is shared_ptr, hold 100_obj4 address: " << r2 << " , *r2 is: " << *r2 << std::endl; //0x149605f78, 100
    std::cout << "r2.use_count() : " << r2.use_count() << std::endl; //1, obj4 only has 1 user

    r2 = q2;
    std::cout << "after r2 = q2;" << std::endl;
    //both r2 and q2 point to obj3, obj3 reference count + 1 = 2; 
    //obj4 reference count = 0, memory of obj4 automatically freed by shared_ptr class
    std::cout << "q2 is shared_ptr, hold 42_obj3 address: " << q2 << " , *q2 is: " << *q2 << std::endl; //0x149605f58, 42
    std::cout << "q2.use_count() : " << q2.use_count() << std::endl; //2, obj3 has 2 user r2 q2

    std::cout << "r2 is shared_ptr, hold 42_obj3 address: " << r2 << " , *r2 is: " << *r2 << std::endl; //0x149605f58, 42
    std::cout << "r2.use_count() : " << r2.use_count() << std::endl; //2, obj3 has 2 user r2 q2

    delete q;
    //after delete q, both q = r are invalidated since they point to same obj1, obj1 now freed
    //but q and r still hold the orginal address
    std::cout << "after delete, obj1 mem freed, but q and r still hold orginal obj1 address: " << q << " " << r  << std::endl; //0x149605e70 0x149605e70

    //but obj2 never freed, memory leakage !!!
    delete backup; // now obj2 freed, but backup still hold obj2 address
    std::cout << "after delete, backup still hold obj2 address: " << backup << std::endl; //0x149605fc0

    q = nullptr;
    r = nullptr;
    backup = nullptr;

    return 0;

    //after main(), shared ptr r2, q2 out of scope, they will be destroyed
    // then obj3 will be automatically freed by shared_ptr class

    //output
    // q point int 42_object1, q value is: 0x149605e70 , *q is: 42
    // r point int 100_object2, r value is: 0x149605fc0 , *r is: 100
    // q point int 42_object1, q value is: 0x149605e70 , *q is: 42
    // r now point int 42_object1, r value is: 0x149605e70 , *r is: 42
    // q2 is shared_ptr, hold 42_obj3 address: 0x149605f58 , *q2 is: 42
    // q2.use_count() : 1
    // r2 is shared_ptr, hold 100_obj4 address: 0x149605f78 , *r2 is: 100
    // r2.use_count() : 1
    // after r2 = q2;
    // q2 is shared_ptr, hold 42_obj3 address: 0x149605f58 , *q2 is: 42
    // q2.use_count() : 2
    // r2 is shared_ptr, hold 42_obj3 address: 0x149605f58 , *r2 is: 42
    // r2.use_count() : 2
    // after delete, obj1 mem freed, but q and r still hold orginal obj1 address: 0x149605e70 0x149605e70
    // after delete, backup still hold obj2 address: 0x149605fc0

}