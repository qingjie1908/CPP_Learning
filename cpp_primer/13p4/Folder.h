#ifndef FOLDER
#define FOLDER

#include <string>
#include <iostream>
#include <set>

class Message; //even though we friend class, we still need forward declartion

class Folder{
friend class Message;
friend void swap(Message& lhs, Message& rhs);
friend void swap(Folder& lhs, Folder& rhs);
public:
    explicit Folder(std::string s = ""):name(s){}
    ////this constructor has default argument, it is also the Folder default constructor
    //implicityli initialize the Messages to empty set

    //copy constructor
    Folder(const Folder& orig);

    //copy-assignemnt operator
    Folder& operator=(const Folder& rhs);

    //destructor
    ~Folder();

private:
    std::set<Message*> Messages; //here both key/value type is Message*
    std::string name;


    void addMsg(Message*);
    void remMsg(Message*);
};

#endif