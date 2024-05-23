#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/12p1/StrBlob.h"

int main()
{
    std::string cur_dir = std::filesystem::current_path();
    std::string test_txt_12p20 = cur_dir + "/" + "test_12p20.txt";

    std::ofstream fo;
    fo.open(test_txt_12p20, std::ostream::out); //will truncate the file each time we write to it

    std::vector<std::string> vec_s1 = {"abc", "bb", "cde", "a", "ef"};

    //now write into txt with vec_s1
    for(auto item : vec_s1){
        fo << item << std::endl;
    }

    fo.close();

    //now read from txt a line at a time into a StrBlob obj
    StrBlob obj1;

    //for const obj we need to initialize them imediately or it will keep empty
    const StrBlob obj2({"obj2", "is", "const"});

    std::ifstream fi;
    fi.open(test_txt_12p20);

    std::string line; //store each line read from txt
    while(getline(fi, line)){
        obj1.push_back(line); //push_back is StrBlob::push_back()
        //obj2.push_back(line); //wrong obj2 is const obj
    }

    fi.close();

    //now use a StrBlobPtr to print each element
    //StrBlobPtr p1(obj1); //now p1.curr is default to 0

    auto iter = obj1.begin(); //iter now is a StrBlobPtr

    //below defination is not correct
    //because obj2.begin() will call construnctor StrBlobPtr(obj2),
    //but the constructor take non-const reference, we cannot bind non-const reference to const obj2
    //auto iter2 = obj2.begin();

    //so we need to add constructor for const obj
    //we also need to add const member func for begin and end()
    auto iter2 = obj2.begin();

    //note the StrBlobPtr class only read the obj, not change it, so we don't need to modify the member func in this class


    // while(iter != obj1.end()){ //no != operator defined in StrBlobPtr class

    // }

    //if curr and wptr are public we can use this: while (iter.curr != (iter.wptr.lock())->size())
    //we cannot use weak ptr to access object directly since it might point to non-exist object, use wptr.lock() to get a shared ptr then do access
    while (true)
    {
        std::cout << iter.deref() << std::endl;
        iter.incr();
    }
    //it's not a dead loop for while(true). since iter.deref() and incr() will help index for us
    //at the end when index out of range it will throw exception

    //output
    // abc
    // bb
    // cde
    // a
    // ef
    // libc++abi: terminating due to uncaught exception of type std::out_of_range: dereference past end

    //for const obj2
    while(true)
    {
        std::cout << iter2.deref() << std::endl;
        iter2.incr();
    }
    //output
    /*
    obj2
    is
    const
    libc++abi: terminating due to uncaught exception of type std::out_of_range: dereference past end
    */

    return 0;
}