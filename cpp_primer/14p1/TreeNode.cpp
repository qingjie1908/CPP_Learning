#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/BinStrTree.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/TreeNode.h"
#include <string>
#include <iostream>
#include <memory>

TreeNode::TreeNode(const std::string& name, int pcount, TreeNode* left_node, TreeNode* right_node){
    value = name;
    count = pcount;
    //left/right_node has default argument nullptr
    if (left_node != nullptr) {left = new TreeNode(*left_node);} else left = nullptr;
    if (right_node != nullptr) {right = new TreeNode(*right_node);} else right = nullptr;
}
TreeNode::TreeNode(const TreeNode& orig){
    value = orig.value; //value copy, std::string copy construct
    count = orig.count; //value copy, int copy construct

    if(orig.left != nullptr){
       left = new TreeNode(*orig.left); //value copy, call copy construct when TreeNode(*orig.left)
    } else {left = nullptr;}
   
    if(orig.right != nullptr){
        right = new TreeNode(*orig.right); //call copy construct, until left right is nullptr
    } else {right = nullptr;}
    std::cout << "TreeNode copy construct" << std::endl;
}
TreeNode& TreeNode::operator=(const TreeNode& rhs){
    if(this != &rhs){
        value = rhs.value;
        count = rhs.count;
        //now free lhs orignal contents
        free();

        if(rhs.left != nullptr){
            TreeNode* temp_left = new TreeNode(*(rhs.left)); //call copy constrcutor TreeNode(rhs)
            left = temp_left;
        } else {
            left = nullptr;
        }

        if(rhs.right != nullptr){
            TreeNode* temp_right = new TreeNode(*(rhs.right)); //call copy constrcutor TreeNode(rhs)
            right = temp_right;
        } else {
            right = nullptr;
        }
        //after scope, temp here is not TreeNode object, it's a built-in pointer, so its destroy temp, which is built-in pointer, will not call destructor
        //lhs still hold the address of contents temp orignally pointed to,
    }
    //if this == &rhs, do nothing,
    
    std::cout << "TreeNode copy assignment" << std::endl;
    return *this;
}

void TreeNode::free(){
    delete left;
    delete right;
    left = right = nullptr;
}

TreeNode::~TreeNode(){
    free();
    std::cout << "TreeNode destructor" << std::endl;
}

//output operator
std::ostream& operator<<(std::ostream& os, const TreeNode& obj){
    os << obj.value << " ";
    if(obj.left != nullptr){
        os << "has left: " << (obj.left)->value << "; "; //here << is std <<
        os << *(obj.left); //here << is own defined operator
    } else {
        os << "has no left node; ";
    }

    os << obj.value << " ";
    if(obj.right != nullptr){
        os << "has right: " << (obj.right)->value << "; ";
        os << *(obj.right);
    } else {
        os << "has no right node; ";
    }

    return os;
}

//input operator, need to chec its state
std::istream& operator>>(std::istream& is, TreeNode& obj){
    is >> obj.value; //write a string to obj.value, this is std::>>
    //value should be a string, if we want value has ceratin format, for example first char should be alpha
    //then if it's not, we can set is::fail_bit, which will may is.fail() to 'true'
    if (obj.value.empty() || !isalpha(obj.value[0])){
        is.setstate(std::ios_base::failbit); //now is.fail() is true, is change to invalid state
        std::cout << "Read into TreeNode obj fail, first char should be a letter, reset obj value to empty string" << std::endl;
        obj.value = "";
    }
    return is; //now in user code, next while(is >> obj) will not be executed
}

bool operator==(const TreeNode& lhs, const TreeNode& rhs){
    bool left_bool, right_bool;
    if(lhs.left != nullptr && rhs.left != nullptr){
        left_bool = (*(lhs.left) == *(rhs.left));
    } else if (lhs.left == nullptr && rhs.left == nullptr) {
        left_bool = true;
    } else left_bool = false;

    if(lhs.right != nullptr && rhs.right != nullptr){
        right_bool = (*(lhs.right) == *(rhs.right));
    } else if (lhs.right == nullptr && rhs.right == nullptr) {
        right_bool = true;
    } else right_bool = false;

    return (lhs.value == rhs.value) && (lhs.count == rhs.count) && left_bool && right_bool;

}
bool operator!=(const TreeNode& lhs, const TreeNode& rhs){
    return !(lhs == rhs);
}