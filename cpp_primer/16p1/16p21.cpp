#include <iostream>

class DebugDelete{
public:
    DebugDelete(std::ostream& os_p = std::cout):os(os_p){}
    template<typename T> void operator()(T* p){ delete p; os << "delete called" << std::endl;}
private:
    std::ostream& os;
};


int main()
{
    {
        std::unique_ptr<int, DebugDelete> up_1(new int(5), DebugDelete());
    }
    //delete called
}