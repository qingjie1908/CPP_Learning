#include <memory>
#include <string>
#include <iostream>

class TreeNode{
public:
    //default constructor
    TreeNode():count(0), left(nullptr), right(nullptr){++unique_id; value = "n" + std::to_string(unique_id);}
    TreeNode(std::string s, int i, TreeNode* n1, TreeNode* n2):value(s), count(i){

            ////note this direct initialized constructor value copy to new memory, not copy pointer
            //so if we create obj1("name", 2, &obj2, &obj3)
            //it not add obj2,3 as obj1 left right node, but create another two new nodes with same contents as obj2,3
            //and use those two nodes as obj1 sub nodes,
            if(n1 != nullptr) left = new TreeNode(*n1); else left =nullptr;
            if(n2 != nullptr) right = new TreeNode(*n2); else right = nullptr;
        } 

    //copy consturctor
    TreeNode(const TreeNode& orig);

    //assignment operator
    TreeNode& operator=(const TreeNode& rhs);

    //destructor
    ~TreeNode(){
        if(left != nullptr){ //for obj use default constructor, it will not delte nullptr
                             //for obj use copy initialized or direct initialized, left right point to dynamic memory, can use delete 
            std::cout << "call destructor of [" << value << "] since its left not null;" << std::endl;
            delete left;
        }

        if(right != nullptr){
            std::cout << "call destructor of [" << value << "] since its right not null;" << std::endl;
            delete right;
        }
    }

    std::string value; //able to change node name for debug

private:
    //std::string value;
    int count;
    TreeNode *left;
    TreeNode *right;
    static int unique_id; // for those obj initialize with default constructor
};

int TreeNode::unique_id = 0;

//copy constructor
//      1
//   2     3
//  4 5   6 7
TreeNode::TreeNode(const TreeNode& orig){

    //built in type int and string will automaticaaly create a different address with, not copy pointer
    value = orig.value;
    count = orig.count;

    //TreeNode left right should be value copied, not pointer copy
    if (orig.left != nullptr)
        left = new TreeNode(*orig.left); //cannot dereference a nullptr
    else left = nullptr;

    if (orig.right != nullptr)
        right = new TreeNode(*orig.right);
    else right = nullptr;

}

//assignment operator
//consider self assignment also
TreeNode& TreeNode::operator=(const TreeNode& rhs){
    value = rhs.value;
    count = rhs.count;

    TreeNode* left_tmp = new TreeNode(*rhs.left);
    //left_temp is built in pointer, point to dynamic memory
    //when = operator func ends, left_temp this pointer destroyed
    //but that dynamic memory still exists, and we allocate it to this.left to manage
    //so that dynamic memory free responsibility is in this class destructor
    if(left != nullptr){
        delete left;
        left = left_tmp;
    } else { //is null ptr, can also delete nullptr
        left = left_tmp;
    }

    TreeNode* right_tmp = new TreeNode(*rhs.right);
    if(right != nullptr){
        delete right;
        right = right_tmp;
    } else {
        right =  right_tmp;
    }
    return *this;
}

int main()
{
    //note all member in TreeNode are private, if we want to create a tree, need to start from the lowest level to top
    //        1
    //   2         3        
    // 4   5     6   null

    TreeNode n4, n5, n6; //default consturctor, left and right are null ptr, there unique name are "n1", "n2", "n3" given by static unique id

    std::string n2_name = "n2", n3_name = "n3", n1_name = "n1";

    TreeNode n2(n2_name, 2, &n4, &n5);
    TreeNode n3(n3_name, 3, &n6, nullptr);
    TreeNode n1(n1_name, 1, &n2, &n3);

    std::cout << "finish free all memory." << std::endl;

    //output
    //destructor destroy variable in reverse order
    //the first five line are delte n1 node;
    //the sixth line are delte n3 node, left, n6, which has null ptr subnodes
    //the line7,8 are delte n2 node, left n4, right n5, which has null ptr subnodes

    //note n1 sub nodes just has same name "n2", "n3", but they are new nodes, not n2 n3 node
    /*
    call destructor of [n1] since its left not null;
    call destructor of [n2] since its left not null;
    call destructor of [n2] since its right not null;
    call destructor of [n1] since its right not null;
    call destructor of [n3] since its left not null;
    call destructor of [n3] since its left not null;
    call destructor of [n2] since its left not null;
    call destructor of [n2] since its right not null;
    */

    //if add below command, run with before command together
    TreeNode n7("n7", 7, &n4, nullptr);

    n7 = n1;

    //output
    //line 1-5 is node n7 destructor, the have same contents with n1 but in different memory
    //line 6-10 is node n1 destructor
    //line 11 is n3 destructor
    //line 12,13 is n2 destructor
    //n4,5,6 subnodes are null ptr so no message print
    
    /*
    1) call destructor of [n1] since its left not null;
    2) call destructor of [n2] since its left not null;
    3) call destructor of [n2] since its right not null;
    4) call destructor of [n1] since its right not null;
    5) call destructor of [n3] since its left not null;
    6) call destructor of [n1] since its left not null;
    7) call destructor of [n2] since its left not null;
    8) call destructor of [n2] since its right not null;
    9) call destructor of [n1] since its right not null;
    10) call destructor of [n3] since its left not null;
    11) call destructor of [n3] since its left not null;
    12) call destructor of [n2] since its left not null;
    13) call destructor of [n2] since its right not null;
    */
    
}
