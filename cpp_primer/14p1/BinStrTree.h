#ifndef BINSTRTREE
#define BINSTRTREE
#include <string>
class TreeNode; //forwad class declaration, incomplete type, cannot derefence or call its member func (including constructor) in this header file cause we do not know what's in it

class BinStrTree{
friend class TreeNode;
friend std::ostream& operator<<(std::ostream& os, const BinStrTree& obj);
public:
    BinStrTree():tree_name(""), root(nullptr){} //default constructor
    BinStrTree(const std::string& pname = "", TreeNode* proot = nullptr); //first paramenter has default argument, the its following all parameters need defaulg argument
    //copy constructor
    BinStrTree(const BinStrTree& orig);
    //copy assignment
    BinStrTree& operator=(const BinStrTree& rhs);
    //desturctor
    ~BinStrTree();

private:
    std::string tree_name;
    TreeNode *root;
    void free();
};

//output operator
std::ostream& operator<<(std::ostream& os, const BinStrTree& obj);

#endif