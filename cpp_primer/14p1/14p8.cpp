#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/BinStrTree.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/TreeNode.h"

int main()
{
    TreeNode n1("n1"), n2("n2"), n3("n3"), n4("n4");
    TreeNode n5("n5", &n1, &n2); //just copy contents of n1, n2, not taking exatc n1, n2 to be n5 subnodes, so n5.left != &n1, new address // two copy construct; and count = 2, has two not null subnodes
    TreeNode n6("n6", &n3, &n4); //two copy construct
    TreeNode n7("n7", &n5, &n6); //six copy construct, n5 has two subnodes, n6 has two subnodes, plus n5, n6 total six, count = 6, has 6 subnodes

    TreeNode n8(n7); // 7 copy construct, n8 has seven subnodes

    n8 = n6; //first, free() will delete n8 orginal left, right, total 6 subnodes, call 6x destructor, then 2x copy construct for n8 new subnodes n3,n4, then all these steps combined to make copy assignment for n8 = n6

    //out of program, destroy n8(total 3 nodes), n7(7 nodes), n6(3 nodes), n5(3 nodes), n4,n3,n2,n1, total 20x destructor called

    BinStrTree BT1("BT1", &n7); //copy value of n7, "7x TreeNode copy constructor"
    BinStrTree BT2(BT1); // "7x TreeNode copy constructor", "1x BinStrTree copy constructor"

    BT2 = BT1; //&BT2, &BT1 are different, just contents value and count are same, 
    //first free() orginal BT2, delete BT2.root, totoal 7 nodes (including root), "7x TreeNode destructor call"
    //then construct new 7x TreeNode, so "7x TreeNode copy construct call"
    //then all above steps make 1x "BinStrTree copy assignment" 

    //out of program, 7x TreeNode destructor, then 1x BT2 BinStrTree destructor, 7x TreeNode destructor, then 1x BT1 BinStrTree destructor,

    //output
    // 17
    // TreeNode copy construct
    // 6
    // TreeNode destructor
    // 2
    // TreeNode copy construct
    // TreeNode copy assignment
    
    // 14
    // TreeNode copy construct
    // BinStrTree copy construct
    // 7
    // TreeNode destructor
    // 7
    // TreeNode copy construct

    //ex 14.8
    std::cout << n7 << std::endl;
    //output
    /*
    n7 has left: n5; n5 has left: n1; n1 has no left node; n1 has no right node; n5 has right: n2; n2 has no left node; n2 has no right node; n7 has right: n6; n6 has left: n3; n3 has no left node; n3 has no right node; n6 has right: n4; n4 has no left node; n4 has no right node; 
    */
    std::cout << BT2 << std::endl;
    /*
    BT1 has root: n7; n7 has left: n5; n5 has left: n1; n1 has no left node; n1 has no right node; n5 has right: n2; n2 has no left node; n2 has no right node; n7 has right: n6; n6 has left: n3; n3 has no left node; n3 has no right node; n6 has right: n4; n4 has no left node; n4 has no right node; 
    */

    if(n8 == n6) { std::cout << "n8 = n6" << std::endl;} //true
    if(BT1 == BT2) {std::cout << "BT1 = BT2" << std::endl;} //true

    //ex14.19 < opeartor for treenode and BinStrTree
    //n1 < n2; //true, compare name "n1" < "n2"
    //n4 < n3; //false, comapre name "n4" < "n3"
    //n5 < n6; //true, compare "n5" < "n6"

    TreeNode A("A"), B("B"), C("C"), D("D");
    TreeNode N1("N1", &A, nullptr), N2("N1", nullptr, &A);
    //N1 < N2; //false, N1.left not null, N2 left null
    TreeNode N3("N3", &N1, nullptr), N4("N3", &N1, &A);
    //N3 < N4; //true, subnodes count N3 < N4
    TreeNode N5("N5", &N1, &A), N6("N5", &N1, &B);
    //N5 < N6; //true, subnode right A <  right B
    TreeNode N7("N7", &A, &B), N8("N7", &B, &B);
    //N7 < N8; // true, subnode left A < left B

    TreeNode NN1(std::move(N1)); //move constructor
    TreeNode NN2;
    NN2 = std::move(NN1); //move assignment

    return 0;
}