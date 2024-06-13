#ifndef TREENODE
#define TREENODE
#include <string>
#include <iostream>

class TreeNode {
friend class BinStrTree;
friend std::ostream& operator<<(std::ostream& os, const TreeNode& obj); //TreeNode output operator
friend std::istream& operator>>(std::istream& is, TreeNode& obj); //TreeNode input operator
friend std::ostream& operator<<(std::ostream& os, const BinStrTree& obj); //BinStrTree output operator
friend std::istream& operator>>(std::istream& is, BinStrTree& obj); //BinStrTree input operator
friend bool operator==(const TreeNode& lhs, const TreeNode& rhs);
friend bool operator!=(const TreeNode& lhs, const TreeNode& rhs);
friend bool operator<(const TreeNode& lhs, const TreeNode& rhs);
public:
    TreeNode():value(std::string()), count(0), left(nullptr), right(nullptr){}
    TreeNode(const std::string& name);
    TreeNode(const std::string& name, TreeNode* left_node, TreeNode* right_node);
    TreeNode(const TreeNode& orig);
    TreeNode(TreeNode&& orig); //move constructor
    TreeNode& operator=(const TreeNode& rhs); //copy assignment
    TreeNode& operator=(TreeNode&& rhs); //move assignment
    TreeNode& operator=(const std::string ps); //assignment operator just change string value
    ~TreeNode();

    //conversion operator
    explicit operator bool() {return left != nullptr || right != nullptr;}
    std::string value;
    
private:
    //std::string value;
    int count; //has how many sub nodes(not null)
    TreeNode* left;
    TreeNode* right;
    void free();
};

//output operator
std::ostream& operator<<(std::ostream& os, const TreeNode& obj);
//input operator
std::istream& operator>>(std::istream& is, TreeNode& obj);

bool operator==(const TreeNode& lhs, const TreeNode& rhs);
bool operator!=(const TreeNode& lhs, const TreeNode& rhs);
bool operator<(const TreeNode& lhs, const TreeNode& rhs);
#endif