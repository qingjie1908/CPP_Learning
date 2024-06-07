#ifndef TREENODE
#define TREENODE
#include <string>
#include <iostream>

class TreeNode {
friend class BinStrTree;
friend std::ostream& operator<<(std::ostream&, const TreeNode& obj);
friend std::ostream& operator<<(std::ostream& os, const BinStrTree& obj);
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
#endif