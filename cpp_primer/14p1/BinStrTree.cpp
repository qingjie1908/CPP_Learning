#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/BinStrTree.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/14p1/TreeNode.h"
#include <string>
#include <iostream>

BinStrTree::BinStrTree(const std::string& pname, TreeNode* proot){ //note declaration already have default argument, cannot add default argument here, otherwise it's re-definantion error
    //we want to value copy TreeNode proot, instead of poitner copy
    //each BinStrTree is different
    if (proot != nullptr){
        root = new TreeNode(*proot); //copy constructor of TreeNode
    } else {
        root = nullptr;
    }
    tree_name = pname;
}

BinStrTree::BinStrTree(const BinStrTree& orig){

    if(orig.root != nullptr){
        root = new TreeNode(*(orig.root));
    } else {
        root = nullptr;
    }
    tree_name = orig.tree_name;
    std::cout << "BinStrTree copy construct" << std::endl;
}

BinStrTree& BinStrTree::operator=(const BinStrTree& rhs){

    if(this != &rhs) { //not self assignment
        free();
        tree_name = rhs.tree_name;
        if(rhs.root != nullptr){
            root = new TreeNode(*(rhs.root)); //TreeNode copy constructor
        } else {
            root = nullptr;
        }
    }
    //else this = &rhs, do nothing
    std::cout << "BinStrTree copy assignment" << std::endl;
    return *this;
}

void BinStrTree::free(){
    delete root;
    root = nullptr;
}

BinStrTree::~BinStrTree(){
    free();
    std::cout << "BinStrTree destructor" << std::endl;
}