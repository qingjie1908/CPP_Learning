#ifndef MESSAGE
#define MESSAGE

#include <vector>
#include <set>
#include <iostream>
#include <string>

class Folder; //even if we friend class Folder, we still need forward declartion

class Message{
friend class Folder;
friend void swap(Message& lhs, Message& rhs);
friend void swap(Folder& lhs, Folder& rhs);
public:
    explicit Message(const std::string &str=""):contents(str){}
    //this constructor has default argument, it is also the Message default constructor
    //implicityli initialize the folders to empty set

    //copy constructr
    Message(const Message& orig);
    //copy assignment
    Message& operator=(const Message& rhs);

    //copy assignment using copy constructor and swap, not wanted
    //Message& operator=(Message rhs_copy);
    //when copy constructor to initialize rhs_copy, pass by value not reference
    //but swap is pass by reference
    //so all swap only influence rhs_copy.folders, not influence rhs.folders;
    //thier set folders member address is different; not wanted

    //move constructor
    //insert element to set moght throw exception, like not enough memory left, bad_alloc
    //so we will not mark them as no except, same for folder class
    Message(Message&& orig);

    //move operator
    Message& operator=(Message&& rhs);

    //destructor
    ~Message();

    //add/remove this Message from the specified Folder's set of message
    void save(Folder& f);
    void remove(Folder& f);

private:
    std::string contents; //actual message text
    std::set<Folder*> folders; //floders that save this message 

    //utility function used by copy constructor, assignment, and destructor

    //add this Message to the Floders that point to the paramenter
    //like add "hello" to folders in which has "qingjie"
    void add_to_Folders(const Message&);

    //remove this Message from every Folders in folders
    void remove_from_Folders();

};

#endif