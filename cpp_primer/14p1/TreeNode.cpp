#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/BinStrTree.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/TreeNode.h"
#include <string>
#include <iostream>
#include <memory>

TreeNode::TreeNode(const std::string& name, int pcount, TreeNode* left_node, TreeNode* right_node){
    value = name;
    count = pcount;
    //left/right_node has default argument nullptr
    if (left_node != nullptr) left = new TreeNode(*left_node); else left = nullptr;
    if (right_node != nullptr) right = new TreeNode(*right_node); else right = nullptr;
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