#include <string>

template <typename T> T mmax(const T& v1, const T& v2){
    return v1 < v2 ? v2 : v1;
}

template <typename T> int mcompare(const T& v1, const T& v2){
    if(v1 < v2) return -1;
    if(v2 < v1) return 1;
    return 0;
}

int main(){
    int i = 3;
    double j = 5.0;

    auto ret1 = mmax(i, j); //error, deduce two different type
    auto ret2 = mmax<int>(i, j); //ok, explicit specify tempalte paramter type, normal conversion apply, double to int
    auto ret3 = mmax<double>(i, j); //ok, int to double

    auto ret4 = mcompare("aa", "bbb"); //error, type different, const char [3] and const char [4]
    auto ret5 = mcompare<std::string>("aa", "bbb"); //ok, type is const string&
    auto ret6 = mcompare<char*>("aa", "bbb"); //ok, type is const char*, but compare pointer meaningless

    return 0;
}