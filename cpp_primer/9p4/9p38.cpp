#include <iostream>
#include <vector>
#include <string>

int main()
{
    //==== "ex 9.38" ====
    std::vector<int> ivec;
    std::cout << "ivec: size: " << ivec.size() //0
    << " capacity: " << ivec.capacity() << std::endl; //0

    for (std::vector<int>::size_type ix = 0; ix != 24; ++ix)
         ivec.push_back(ix);
    std::cout << "ivec: size: " << ivec.size() //24
    << " capacity: " << ivec.capacity() << std::endl; //32

    ivec.reserve(50);
    std::cout << "ivec: size: " << ivec.size() //24
    << " capacity: " << ivec.capacity() << std::endl; //50

    while (ivec.size() != ivec.capacity())
         ivec.push_back(0);
    std::cout << "ivec: size: " << ivec.size() //50
    << " capacity: " << ivec.capacity() << std::endl; //50

    ivec.push_back(42); // add one more to excess capacity
    std::cout << "ivec: size: " << ivec.size() //51
    << " capacity: " << ivec.capacity() << std::endl; //100
    
    ivec.shrink_to_fit(); //ask for the memory to be returned, not guranteed
    //// size should be unchanged; capacity is implementation defined
    std::cout << "ivec: size: " << ivec.size() //51
    << " capacity: " << ivec.capacity() << std::endl; //51

    //==== "ex 9.39" ====
    std::vector<std::string> svec;
    std::cout << "svec: size: " << svec.size() //0
    << " capacity: " << svec.capacity() << std::endl; //0

    svec.reserve(1024);
    std::cout << "svec: size: " << svec.size() //0
    << " capacity: " << svec.capacity() << std::endl; //1024

    //====input 256 words
    int n = 0;

    while(n < 256){
        svec.push_back("hello");
        ++n;
    }
    std::cout << "svec: size: " << svec.size() //256
    << " capacity: " << svec.capacity() << std::endl; //1024

    svec.resize(svec.size() + svec.size()/2); // append empty string in svec
    std::cout << "svec: size: " << svec.size() //384
    << " capacity: " << svec.capacity() << std::endl; //1024

    //====input 512 words
    svec.clear();
    n = 0;

    while(n < 512){
        svec.push_back("hello");
        ++n;
    }
    std::cout << "svec: size: " << svec.size() //512
    << " capacity: " << svec.capacity() << std::endl; //1024

    svec.resize(svec.size() + svec.size()/2);
    std::cout << "svec: size: " << svec.size() //758
    << " capacity: " << svec.capacity() << std::endl; //1024

    //====input 1000 words
    svec.clear();
    n = 0;

    while(n < 1000){
        svec.push_back("hello");
        ++n;
    }
    std::cout << "svec: size: " << svec.size() //1000
    << " capacity: " << svec.capacity() << std::endl; //1024

    svec.resize(svec.size() + svec.size()/2);
    std::cout << "svec: size: " << svec.size() //1500
    << " capacity: " << svec.capacity() << std::endl; //2048

    //====input 1048 words
    svec.clear();
    n = 0;

    while(n < 1048){
        svec.push_back("hello");
        ++n;
    }
    std::cout << "svec: size: " << svec.size() //1048
    << " capacity: " << svec.capacity() << std::endl; //2048

    svec.resize(svec.size() + svec.size()/2);
    std::cout << "svec: size: " << svec.size() //1572
    << " capacity: " << svec.capacity() << std::endl; //2048

    return 0;

}