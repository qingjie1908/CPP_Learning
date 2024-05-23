#include <memory>

int main()
{
    int ix = 1024, *pi = &ix, *pi2 = new int(2048);

    typedef std::unique_ptr<int> IntP;

    //1. type mismatch
    //error: no matching constructor for initialization of 'IntP' (aka 'unique_ptr<int>')
    //IntP p0(ix);

    //2. when we define a unique_ptr, we bind it to a pointer returned by new
    // when pass built-in pointer, we also need to pass the deleter type in define
    //IntP p1(pi);
    //exception: cannot delete an incomplete type

    //3. pi2 is pointer return by new, legal
    IntP p2(pi2);

    //4.
    //IntP p3(&ix);
    //exception: cannot delete an incomplete type"
    //same as case 2

    //5. directly initialize, legal
    IntP p4(new int(2048));

    //6. p2.get()
    IntP p5(p2.get());
    //exception: cannot delete an incomplete type"
}