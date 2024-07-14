#include <bitset>
#include <string>
#include <iostream>

int main()
{
    std::bitset<64> bitvec(32);
    //32 convert to unsigned long long
    for(int i = bitvec.size()-1; i >= 0; --i){
        std::cout << bitvec[i];
    }
    std::cout << std::endl;
    //0000000000000000000000000000000000000000000000000000000000100000

    std::bitset<32> bv(1010101);
    //1010101 convert to unsigned long long, still decimal
    for(int i = bv.size()-1; i >= 0; --i){
        std::cout << bv[i];
    }
    std::cout << std::endl;
    //00000000000011110110100110110101

    std::string bstr; //"101100"
    std::cin >> bstr;
    std::bitset<8> bv2(bstr);
    for(int i = bv2.size()-1; i >= 0; --i){
        std::cout << bv2[i];
    }
    std::cout << std::endl;
    //00101100
}