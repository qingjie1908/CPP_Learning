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
public:
    TreeNode():value(std::string()), count(0), left(nullptr), right(nullptr){}
    TreeNode(const std::string& name = "", int pcount = 0, TreeNode* left_node = nullptr, TreeNode* right_node = nullptr);
    TreeNode(const TreeNode& orig);
    TreeNode& operator=(const TreeNode& rhs);
    ~TreeNode();
    
private:
    std::string value;
    int count;
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
#endif