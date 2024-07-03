template<class T> int compare(const T&, const T&);

template<typename T> T calc(T, int);
template<typename T> T fcn(T, T);

template<typename T> void f1(T, T);
template<typename T1, typename T2> void f2(T1, T2);



int main(){
    compare(1,2); //T is int
    compare("hi", "world");// T is const char [3] and const char [6], different
    compare("bye", "dad"); // T is const char [4]

    double d; float f; char c;
    calc(c, 'c'); //ok, 'c' to int, int is not template paramter, can convert
    calc(d, f); //ok, float to int, int is not template paramter, can convert
    fcn(c, 'c'); //ok, 'c' is const char, but is pass to template paramter by copy, not by reference, so ok
    fcn(d, f); //not ok, first is double, second is float, not same

    int i = 0, j = 42, * p1 = &i, * p2 = &j;
    const int* cp1 = &i, * cp2 = &j;

    f1(p1, p2); //T is int*, f1<int*>(int*, int*)
    f2(p1, p2); //f2<int*, int*>(int*, int*)
    f1(cp1, cp2); //f1<const int*>(const int*, const int*)
    f2(cp1, cp2); //f2<const int*, const int*>(const int*, const int*)
    f1(p1, cp1); //error, two different type
    f2(p1, cp1); //f2<int*, const int*>(int*, const int*)
    
    return 0;
}