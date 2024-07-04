template<typename T> void g(T&& val) {
    vector<T> v;
}
template<typename T> void g2(const T& val);

int main()
{
    int i = 0;
    const int ci = i;

    g(i); // i is lvalue, T is int&, T&& (int& &&) collapse to int&, not int&&
    g(ci); //ci is lvalue, T is const int&, T&& (const int& &&) collapse to const int&
    g(i*ci); //i*ci is rvalue, T is int, T&& is int&&
    g(i = ci); //i = ci; get updated i; still lvalue, T is int&


    g2(i); // i is lvalue, T is int, 
    g2(ci); //ci is lvalue, T is int
    g2(i*ci); //i*ci is rvalue, T is int
    g2(i = ci); //i = ci; get updated i; still lvalue, T is int

    g(42); //42 is rvalue, so instantiation is void g(int&& val), T is int
}