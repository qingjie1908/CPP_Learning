#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Message.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Folder.h"

int main()
{
    Message M1("A"), M2("B"), M3("C"), M4("D"), M5("E");

    Folder F1("F1"), F2("F2"), F3("F3"), F4("F4"), F5("F5");

    M1.save(F1); M1.save(F2);
    M2.save(F2); M2.save(F3);
    M3.save(F3); M3.save(F4); M3.save(F5);
    M4.save(F5);
    M5.save(F1); M5.save(F2); M5.save(F3); M5.save(F4); M5.save(F5);

    Message M_T1; //M_T1 object has new address

    M_T1 = M1; //&M_T1 is different thant &M1 
    //&(M1.folder) and &(M_T1.folders) are also different, they are different set
    //just inside set, they contain same Folder pointer value &F1, &F2

    Message M_T2(M2);

    Folder F_T1;

    F_T1 = F1;

    Folder F_T2(F2);

    swap(M_T1, M_T2);

    swap(F_T1, F_T2);

    return 0;

}