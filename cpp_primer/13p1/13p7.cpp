#include <memory>
#include <string>
#include <vector>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/12p1/StrBlob.h"

int main()
{
    StrBlob obj1, obj2;
    //obj1.data 0x98, obj2.data oxc8, point to different memory


    StrBlobPtr obj1_ptr(obj1), obj2_ptr(obj2);
    //obj1_ptr.wptr is 0x98, obj2_ptr.wptr is 0xc8

    obj1 = obj2; //use default systhesized copy assignment operator,
    // obj1.data and obj2.data has same address 0xc8, so 0x98 freed
    // obj1_ptr.wptr is 0x98, obj2_ptr.wptr is 0xc8
    // so obj1_ptr.wptr.lock() is false since 0x98 memory freed, this will return null shared_ptr



    obj1_ptr = obj2_ptr; // both wptr = 0xc8, .lock() is true, not expire

}