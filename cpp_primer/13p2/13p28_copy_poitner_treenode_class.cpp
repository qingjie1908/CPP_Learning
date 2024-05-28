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
            /*
            if(n1 != nullptr) left = new TreeNode(*n1); else left =nullptr;
            if(n2 != nullptr) right = new TreeNode(*n2); else right = nullptr;
            */

            //pointer copy constructor not value copy
            //add real obj2 and obj3 as subnodes, not a new memory of same contents as obj2 and obj3
            left = n1;
            right = n2;
        } 

    //copy consturctor
    TreeNode(const TreeNode& orig);

    //assignment operator
    TreeNode& operator=(const TreeNode& rhs);

    //destructor
    //no need cause our whole class has not use directly dynamic memory by "new"
    ~TreeNode(){
        //program will destroy string value, int count and normal built-in pointer TreeNode* by them
        //we do not need delete TreeNode, cause it's not dynamic by new, also it's not dynamic at all, just point to local variable
        //delete p; if illegal if p point to local variable
        std::cout << "Program self take care of destory " << value << std::endl;
    }

    std::string value;

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
        *left = *orig.left; //cannot dereference a nullptr
    else left = nullptr;

    if (orig.right != nullptr)
        *right = *orig.right;
    else right = nullptr;

}

//assignment operator
//consider self assignment also
TreeNode& TreeNode::operator=(const TreeNode& rhs){
    value = rhs.value;
    count = rhs.count;

    //note, our constructor does not use new to allocate dynamic memory
    //if = operator allocate dynamic memory by new, it's hard to maintain destructor
    //cause we do not know if the object is constructed(which has no dynamic memory by using new), like obj3(&obj1, &obj2);, obj1, obj2 default initialized
    //or the obj has been applied new value by "=" operator
    //so delete will have error because we cannot delte a normal built-in pointer, which not point to dynamic memory, delete &obj1 is not allowed
    //so in "=" operator, we should avoid directly allocate dynamic memory by new

    //also for self assignment, we should not update lhs pointer value
    //because it may break the chain of its father node
    //like obj1(obj2, obj3), now &obj2 is 0x1
    //if obj2 = obj2 change &obj2 to 0x2 and free 0x1, then *obj1.obj2 would be disaster
    //so = operator not change lhs address, only copy value and count and pointer address

    // if ((rhs.left != nullptr) && (left != nullptr)) {
    //     *left = *rhs.left;
    // } else if ((rhs.left != nullptr) && (left == nullptr)){ //then we cannot *left
    //     //now this.left = 0x00000000
    //     //create a new TreeNode to subsititute this.left nullptr
    //     //if we use below local variable way
    //     //when = operator finished, new_obj_left will be detroyed
    //     //so as this.left
    //     /*
    //     TreeNode new_obj_left; //now &new_obj_left is not 0x00000
    //     left = &new_obj_left;
    //     */

    //     auto new_obj_left = std::make_shared<TreeNode>();
    //     //left = new_obj_left; wrong left is not a smart ptr, it's built in ptr
    //     left = new_obj_left.get();

    //     *left = *rhs.left;
    // } else if (rhs.left == nullptr){
    //     left = nullptr;
    // }

    // //if rhs contain nullptr, left also transfer to null ptr,
    // //lhs.left orginal subnodes will be take care of by program cause all our class definaition not use dynamic memory
    // //so when program ends, these subnodes pointer will be destroyed

    // if ((rhs.right != nullptr) && (right != nullptr)) {
    //     *right = *rhs.right;
    // } else if ((rhs.left != nullptr) && (left == nullptr)){ //then we cannot *left
    //     auto new_obj_right = std::make_shared<TreeNode>();

    //     right = new_obj_right.get();
    //     *right = *rhs.right;
    // } else if (rhs.right == nullptr){
    //     right = nullptr; //this.right original subnodes will take care by program since they are built in pointer, not point to dynamic memory by new
    // }

    left = rhs.left;
    right = rhs.right;
    

    return *this;
}

int main()
{
    //note all member in TreeNode are private, if we want to create a tree, need to start from the lowest level to top
    //        1
    //   2         3        
    // 4   5     6   null

    TreeNode n4, n5, n6; //default consturctor, left and right are null ptr, there unique name are "n1", "n2", "n3" given by static unique id
    n4.value = "n4";
    n5.value = "n5";
    n6.value = "n6"; //change them in order to view destructor order when programe ends

    std::string n2_name = "n2", n3_name = "n3", n1_name = "n1";

    TreeNode n2(n2_name, 2, &n4, &n5); //now n2 hold real n4, n5, not another new n4_new n5_new with differnt address
    TreeNode n3(n3_name, 3, &n6, nullptr);
    TreeNode n1(n1_name, 1, &n2, &n3);

    std::cout << "free all memory responsiblity is by program." << std::endl;

    //output
    //destructor destroy variable in reverse order of their declaration
    
    /*
    finish free all memory.
    Program self take care of destory n1
    Program self take care of destory n3
    Program self take care of destory n2
    Program self take care of destory n6
    Program self take care of destory n5
    Program self take care of destory n4
    */

    //if add below command, run with before command together
    //now &n1 = 0x16fdff078
    TreeNode n7("n7", 7, &n4, nullptr); //&n7 = 0x16fdff030

    n7 = n1; //&n7 still 0x16fdff030, but its subnodes change to the same sturcture and address as n1;
    //now n7.value = "n1", change it so to see the destructor order
    n7.value = "n7";

    std::cout << "free all memory responsiblity is by program." << std::endl;

    //output
    /*
    Program self take care of destory n7
    Program self take care of destory n1
    Program self take care of destory n3
    Program self take care of destory n2
    Program self take care of destory n6
    Program self take care of destory n5
    Program self take care of destory n4
    */

    
}
