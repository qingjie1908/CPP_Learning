#include <iostream>
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/16p1/Blob.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/16p1/BlobPtr.h"


int main()
{
    Blob<std::string> Blob_str1({"aa", "bb", "cc", "dd"});
    Blob<std::string> Blob_str2(Blob_str1);
    Blob<std::string> Blob_str3;
    Blob_str3 = Blob_str2;

    std::cout << Blob_str1.back() << std::endl; //dd
    std::cout << Blob_str2.front() << std::endl; //aa

    Blob_str1.pop_back(); 
    Blob_str2.push_back("ee");
    std::cout << Blob_str3[3] << std::endl; //ee

    BlobPtr<std::string> BlobPtr1(Blob_str1);
    BlobPtr<std::string> BlobPtr2(Blob_str2, 2);

    std::cout << *BlobPtr1 << std::endl; //aa
    std::cout << *(BlobPtr1++) << std::endl; //aa
    std::cout << *BlobPtr1 << std::endl; //bb
    std::cout << *BlobPtr2 << std::endl; //cc
    std::cout << *(--BlobPtr2) << std::endl; //bb
    std::cout << *(++BlobPtr1) << std::endl; //cc
    std::cout << *(BlobPtr2--) << std::endl; //bb

    if(BlobPtr1 == BlobPtr2){
        std::cout << "BlobPtr1 == BlobPtr2" << std::endl;
    }

    if(BlobPtr1 < BlobPtr2){
        std::cout << "BlobPtr1 < BlobPtr2" << std::endl;
    }

    if(BlobPtr2 < BlobPtr1){
        std::cout << "BlobPtr2 < BlobPtr1" << std::endl;
    }

    //ex 16.24
    std::vector<std::string> vec1 = {"a", "vv", "sdaf"};
    Blob<std::string> Blob_str4(vec1.begin(), vec1.end()); 

}