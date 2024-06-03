#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Message.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Folder.h"

int main()
{
    Message M1("A");
    Message M2("B");//, M3("C"), M4("D"), M5("E");

    Folder F1("F1"), F2("F2");//, F3("F3"), F4("F4"), F5("F5");

    M1.save(F1); M1.save(F2);
    M2.save(F2); //M2.save(F3);
    // M3.save(F3); M3.save(F4); M3.save(F5);
    // M4.save(F5);
    // M5.save(F1); M5.save(F2); M5.save(F3); M5.save(F4); M5.save(F5);

    Message M_T1; //M_T1 object has new address

    M_T1 = M1; //&M_T1 is different thant &M1 
    //&(M1.folder) and &(M_T1.folders) are also different, they are different set
    //just inside set, they contain same Folder pointer value &F1, &F2

    //if one obj out of scope, it wont affect another obj.folders, set also use value copy

    Message M_T2(M2);

    Folder F_T1;

    F_T1 = F1;

    Folder F_T2(F2);

    swap(M_T1, M_T2);

    swap(F_T1, F_T2);

    //move constructor for Message
    //std::move(M1) return a rvalue reference to obj M1
    //be sure we don't use M1 anymore after this !!!
    Message m1(std::move(M1));

    //move assignment operator for Message
    Message m2(std::move(M2)); //first move construct, be sure M2 not used anymore
    m2 = std::move(m1); //be sure not use m1 anymore

    //folder move constructor
    Folder f1(std::move(F1)); //be sure not sue F1 anymore

    //folder move assignment operator
    Folder f2(std::move(F2));
    f2 = std::move(f1); //not use f1 anymore

    return 0;

}