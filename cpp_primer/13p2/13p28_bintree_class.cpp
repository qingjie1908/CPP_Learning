#include <string>
#include <memory>
#include <iostream>

//use TreeNode class value copy version
class TreeNode{
friend class BinStrTree;
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
        if(left != nullptr){ //for obj use default constructor, it will not need delte nullptr
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
    //left_temp is not built in pointer, but point to dynamic memory
    //when = operator func ends, left_temp this pointer destroyed
    //but that dynamic memory still exists, and we allocate it to this.left to manage
    //so that dynamic memory free responsibility is in this class destructor
    if(left != nullptr){
        delete left;
        left = left_tmp;
    } else { //is null ptr, cannot delete
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


class BinStrTree{
friend class TreeNode;
public:
    //default constructor
    BinStrTree(){root = new TreeNode();}

    //copy constructor
    BinStrTree(const BinStrTree& orig){*root = *orig.root;} //this call TreeNode class copy constructor
    //we want two root are independently, change one root should not affect another root
    //so should use the TreeNode copy value version

    //note for below direct initialization
    //first when pass argument, obj will call copy contructor of TreeNode
    //after BinStrTree(TreeNode obj) call finished, obj will be destoyed, which call TreeNode destructor, so we only need to delte root
 
    BinStrTree(TreeNode obj){
        root = new TreeNode();
        *root = obj; //after this call, obj destroyed, will call destructor
    }

    //copy assignment =operator
    BinStrTree& operator=(const BinStrTree& rhs){
        *root = *rhs.root; //call TreeNode copy assignment operator
        //note since when call TreeNode copy assignment operator
        //we have TreeNode class operator= func to call *root.value = (*rhs.root).value
        //root is private member of calss BinStrStree
        //the TreeNode class take care of self assignment

        return *this;
    }

    //destructor
    ~BinStrTree(){
        std::cout << "BinStrTree " << root->value << " take care by destructor take care by TreeNode destructor " << std::endl;
        delete root; //take care by treenode class
    }

    TreeNode *root;

private:
    //TreeNode *root;
};

int main()
{
    BinStrTree bt1;
    bt1.root->value = "bt1";

    //note left right member in TreeNode are private, if we want to create a tree, need to start from the lowest level to top
    //        1
    //   2         3        
    // 4   5     6   null

    TreeNode n4, n5, n6; //default consturctor, left and right are null ptr, there unique name are "n1", "n2", "n3" given by static unique id
    n4.value = "n4";
    n5.value = "n5";
    n6.value = "n6"; //change them in order to view destructor order when programe ends

    std::string n2_name = "n2", n3_name = "n3", n1_name = "n1";

    TreeNode n2(n2_name, 2, &n4, &n5); //now n2 hold  n4_new, n5_new,  with differnt address than n4, n5
    TreeNode n3(n3_name, 3, &n6, nullptr);
    TreeNode n1(n1_name, 1, &n2, &n3);

    BinStrTree bt2(n1);//now bt2.root is the same as n1, both contents and memory
    //the first 5 line happens here, because when call this, we create temp obj in the func, after this call, temp obj destroyed, call temp_obj destructor
    //&bt2 is 0x070
    bt2.root->value = "bt2";
    
    BinStrTree bt3; //&bt3 is 0x068, only has a TreeNode *root with null ptr subnodes
    bt3 = bt2; //&bt3 is still 0x068, its subnodes are created with new dynamic memory, contens same as bt2 subnodes
    bt3.root->value = "bt3";

    std::cout << "check" << std::endl;
    //output
    //lien 1-5: when call BinStrTree bt2(n1);, we pass n1 to parameter obj, use copy constructor construc obj, then call *root = obj, which call = operator of TreeNode
    //          after this call finished, obj destroyed, which call its destructor
    //line 7-12: call bt3 destructor, which then call treenode destructor
    //line 13-18: call bt2 destructor, which then call trednode destructor
    //line 19-23: call n1 destructor
    //line 24:  call n3 destructor
    //line 25-26: call n2 destructor
    //line 27: call bt1 destructor

    /*
    1)call destructor of [n1] since its left not null;
    2)call destructor of [n2] since its left not null;
    3)call destructor of [n2] since its right not null;
    4)call destructor of [n1] since its right not null;
    5)call destructor of [n3] since its left not null;
    6)check
    7)BinStrTree bt3 take care by destructor take care by TreeNode destructor 
    8)call destructor of [bt3] since its left not null;
    9)call destructor of [n2] since its left not null;
    10)call destructor of [n2] since its right not null;
    11)call destructor of [bt3] since its right not null;
    12)call destructor of [n3] since its left not null;
    13)BinStrTree bt2 take care by destructor take care by TreeNode destructor 
    14)call destructor of [bt2] since its left not null;
    15)call destructor of [n2] since its left not null;
    16)call destructor of [n2] since its right not null;
    17)call destructor of [bt2] since its right not null;
    18)call destructor of [n3] since its left not null;
    19)call destructor of [n1] since its left not null;
    20)call destructor of [n2] since its left not null;
    21)call destructor of [n2] since its right not null;
    22)call destructor of [n1] since its right not null;
    23)call destructor of [n3] since its left not null;
    24)call destructor of [n3] since its left not null;
    25)call destructor of [n2] since its left not null;
    26)call destructor of [n2] since its right not null;
    27)BinStrTree bt1 take care by destructor take care by TreeNode destructor
    */
}