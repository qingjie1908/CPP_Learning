#include <iostream>

int main()
{
    const int i = 42;
    auto j = i; // j is int
    std::cout << j << std::endl;
    const auto &k = i; // k is reference to const int, same as 'auto &k = i';
    auto *p = &i; // p is a pointer to const int, const int *
    const auto j2 = i, &k2 = i; // j2 is const int, k2 is reference to const int i
}