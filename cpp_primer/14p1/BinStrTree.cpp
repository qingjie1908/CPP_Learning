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

//output operator
std::ostream& operator<<(std::ostream& os, const BinStrTree& obj){
    os << obj.tree_name << " "; //<< is std <<
    if(obj.root != nullptr){
        os << "has root: " << obj.root->value << "; ";
        os << *(obj.root); // << is TreeNode version <<
    } else {
        os << "has no node; ";
    }
    return os;
}

//input operator
std::istream& operator>>(std::istream& is, BinStrTree& obj){
    is >> obj.tree_name;
    //we want tree_name start with letter
    if(obj.tree_name.empty() || !isalpha(obj.tree_name[0])){ //not the correct format
        is.setstate(std::ios_base::failbit);
        std::cout << "Tree_name should start with a letter, in valid input." << std::endl;
    }
    return is;
}

bool operator==(const BinStrTree& lhs, const BinStrTree& rhs){
    bool root_bool;
    if(lhs.root != nullptr && rhs.root != nullptr){
        root_bool = (*(lhs.root) == *(rhs.root));
    } else if (lhs.root == nullptr && rhs.root == nullptr){
        root_bool = true;
    } else root_bool = false;

    return (lhs.tree_name == rhs.tree_name) && root_bool;
}
bool operator!=(const BinStrTree& lhs, const BinStrTree& rhs){
    return !(lhs == rhs);
}
bool operator<(const BinStrTree& lhs, const BinStrTree& rhs){
    return (*(lhs.root) < *(rhs.root)); //delegate to TreeNode class < operator
}