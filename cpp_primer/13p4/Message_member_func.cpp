#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Message.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Folder.h"

void Message::save(Folder& f){
    folders.insert(&f);
    f.addMsg(this); //add this Message to f'set of Messages
}

void Message::remove(Folder& f){
    folders.erase(&f);
    f.remMsg(this); //remove this Message to f's set of Messages
}

//add_to_Folders() define
void Message::add_to_Folders(const Message& m){
    for(auto f_p : m.folders){
        (*f_p).addMsg(this); //note this is not change m.folders, since it hold a copy of pointer value
    }
}

//copy constructor
Message::Message(const Message& orig){
    contents = orig.contents;
    folders = orig.folders;

    //now in each folder wher orig appears, this folder should also add "this" new initilized Message
    add_to_Folders(orig);

}
//destructor
//remove this Message from every folder in folders
//note, when all this pointer are removed from the set or the set clear()
//these set and contents still exits, after obj Message or Folder destroyed, they will be handled by the complier to call string and set destructor
void Message::remove_from_Folders(){
    for(auto f_p : folders){
        (*f_p).remMsg(this);
    }

    folders.clear(); //now this.folders set is empty cuase no Folder's Message set contains this Message*
    //but *this Message obj still exist, after out of scope, compiler hander the string and set destructor
}


Message::~Message(){
    remove_from_Folders();
    //The compiler automatically invokes the string de-structor to free contents and the set destructor to clean up the memory used by those members.
}

//copy assignment

Message& Message::operator=(const Message& rhs){

    //remove original lhs in its orginal corresponding folders
    remove_from_Folders();
    //now lhs has empty contents and empty set folders;

    contents = rhs.contents;
    folders = rhs.folders; //now folders only contain Message* point to rhs

    // add "this" to folders
    add_to_Folders(rhs); //now folders also contain Message* point to lhs, which is this

    return *this;
}


//copy assignment using copy constructor and swap, not wanted
/*
Message& Message::operator=(Message rhs_copy){

    swap(*this, rhs_copy);

    //when copy constructor to initialize rhs_copy, pass by value not reference
    //but swap is pass by reference
    //so all swap only influence rhs_copy.folders, not influence rhs.folders;
    //thier set folders member address is different;

    return *this;
}
*/


//non-member func swap
void swap(Message& lhs, Message& rhs)
{
    //we also need to manage the Folder class
    //Folder that hold lhs.contents now should hold rhs.contents
    //before swap, assume A is lhs, B is rhs
    //Message A: "AA", appear in set folders {f1, f2}
    //Message B: "BB", apper in set folders{f2, f3}
    //Folder f1: hold set Messages{A, C, D}
    //Folder f2: hold set Messages{A, B, C, E}
    //Folder f3: hold set Messages{B, D}
    //Folder f4: hold set Message{F}

    //after swap
    //Message A: "BB", apper in set folders{f2, f3}
    //Message B: "AA", appear in set folders {f1, f2}

    //so for Folder we also need to change
    //Folder f1: should hold set Messages {B, C, D}
    //Folder f2: should hold set Messages {A, B, C, E}
    //Folder f3: should hold set Messages {A, D}
    //Folder f4: should hold set Messages {F}
    
    //so what we need to do is before swap contens and folders
    //remove Message A and B from both A.folders (f1, f2) and B.floders set (f2, f3)
    //so remove Message A from f1, f2; now f1 hold {C, D}, f2 hold {B, C, E}
    //then remove Message B from f2, f3; now f2 hold {C, E}, f3 hold {D}

    //after swap
    //add A to new A.folders
    //then new f2: {A, C, E}, new f3: {A, D}
    //then add B to new B.folders
    //then new f1: {B, C, D}, new f2: {A, B, C, E}

    //now Folder f1, f2, f3 has been updated

    //note add duplicate and remove non exist item in set is fine!!!!, but we use the key(the same as value for set)
    //because if use iterator, set.erase(iter), this iter cannot be a non-exist element

    for(auto f_p : lhs.folders){
        f_p->remMsg(&lhs);
    }

    for(auto f_p : rhs.folders){
        f_p->remMsg(&rhs);
    }

    std::swap(lhs.contents, rhs.contents);
    std::swap(lhs.folders, rhs.folders);

    for(auto f_p : lhs.folders){
        f_p->addMsg(&lhs);
    }

    for(auto f_p : rhs.folders){
        f_p->addMsg(&rhs);
    }

}