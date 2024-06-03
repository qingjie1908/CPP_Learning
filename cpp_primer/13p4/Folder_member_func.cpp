#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Message.h"
#include "/Users/qingjie/github/CPP_Learning/cpp_primer/13p4/Folder.h"

void Folder::addMsg(Message* m_p){
    Messages.insert(m_p); //ok, multiple same key will be skipped
}

void Folder::remMsg(Message* m_p){
    Messages.erase(m_p); //ok, erase key can erase non-exist key, earse func cannot earse non-exit iterator point to key
}

//copy constructor
Folder::Folder(const Folder& orig){
    name = orig.name; //value copy

    //Messages pointer copy
    //orig: {A, B, C}
    //after copy, new folder: {A, B, C}
    Messages = orig.Messages;

    //now message also need to add this new folder in their appear folders set
    for(auto m_p : Messages){
        m_p->save(*this); //will add same duplicated Message* into this->Messages, ok, since it a set
    }
}

//copy assignment operator, pointer copy
Folder& Folder::operator=(const Folder& rhs){
    name = rhs.name;

    //orignal lhs {A, B, C}; rhs {B, C, E}
    //now lhs {B, C, E}  
    //so Message element also need to update their appearing folder

    //first remove orginal lhs folder out of A, B, C correspinding folders
    for(auto m_p : Messages){
        m_p->remove(*this); //now lhs is removed from A, B, C folders
    }

    //then copy Messages set
    Messages = rhs.Messages;

    //now lhf {B, C, E}
    //update B, C, E corresponding folder, add *this to folders
    for(auto m_p : Messages){
        m_p->save(*this);
    }

    //also take care off self assinment
    return *this;
}

//move constructor
//noexcept not declare since set may throw exception
Folder::Folder(Folder&& orig){
    name = std::move(orig.name); //use std::string move constructor
    Messages = std::move(orig.Messages); //use std::set move constructor

    //now update 'this'
    for(auto m : Messages){
        m->save(*this);

        //then remove orig from current Message m
        m->folders.erase(&orig);
        //we cannot call m->remove, cause it will then call orig.remMsg, then call orig.Messages.erase(m)
        //we cannot access orig.Messages's resource, since it has been moved, and its value are not guranteed, so we are not suer orig.Messages still hold pointer m (maybe or maybe not)
    }

    //now clear orig.Messages set so it can be destructible
    orig.Messages.clear();

    std::cout << "Folder move constructor called" << std::endl;
    
}

//move assignment operator
//noexcept not declare since set may throw exception
Folder& Folder::operator=(Folder&& rhs){
    //need to check self assignment
    if(this != &rhs){ //lhs and rhs are different obj
        //first update 'this' status before this.Messages be overide by rhs
        for(auto m : Messages){
            //m->remove(*this); //wrong, it will change this.Messages, range for should not change Messages size
            m->folders.erase(this);

        }
        name = std::move(rhs.name); //call std::string move assignment operator
        Messages = std::move(rhs.Messages); //call std::set move assignment operator

        //now update rhs and 'this' new Messages
        for(auto m : Messages){
            m->folders.erase(&rhs); //can not call m->remove, same reason in move constructor
            m->save(*this); //update from Message side
        }

        //now clear rhs set so it can be destructible
        rhs.Messages.clear();
    }
    //else lhs and rhs are same obj, do nothing

    std::cout << "Folder move assignment operator called" << std::endl;

    return *this;

    

}

//destructor
Folder::~Folder(){
    //if Folder hold {A, B, C}
    //first update A,B,C; remove this folder from their appear folders
    //for same reson in swap folder func, we cannot use range for or iterator
    //because socond step in remove will dereference a invalidated iterator

    std::set<Message*> temp_Messages_set = Messages;

    for(auto m_p : temp_Messages_set){ //this will not invalidate temp_Messages_set, temp_Messages_set in still unchanged
        m_p->remove(*this);
    }

    //then clear Messages
    Messages.clear();

}
//Folder obj itself not destroyed, &Folder still exists, it hold an empty Message* set, and its name
//when Folder obj out of scope, compiler takes care of string destructor and set destructor

//swap

void swap(Folder& lhs, Folder& rhs){
    std::swap(lhs.name, rhs.name);

    //lhs:  {A, B, C}
    //rhs:  {B, C, D, E}

    //after swap
    //lhs: {B, C, D, E}
    //rhs: {A, B, C}
    
    //before swap

    //remove() will also remove message* from lhs.Messages
    //we need to first save {A,B,C}, {B,C,D, E}

    std::set<Message*> temp_set_lhs = lhs.Messages; //temp_set_lhs hold {A,B,C}
    std::set<Message*> temp_set_rhs = rhs.Messages; //temp_set_rhs hold {B,C,D,E}
    
    //we cannot use following for loop to erase set
    //You can't do anything that invalidates the range in a range based loop.

    //use iterator cause iterator insert not affect the set, erase only invalida the erased iter
    
    /* follow code is wrong!!!
    for(auto m_p : lhs.Messages){
        m_p->remove(lhs); //A, B, C remove lhs folder in their appear folders
        //also lhs.Messages no longer contain A, B, C
    }
    //now, lhs.Messages is empty set!!!, so std::swap has no meaning, that's why we need to save orginal value in temp set
    */

   //but when use iteraror, remove(lhs) will first earse it then use it again, which is disaster
   //flowing code is alos error
   /*
    for(auto it = lhs.Messages.begin(); it != lhs.Messages.end();){
        //when we call (*it)->remove(lhs); it do following two steps
        // first
        lhs.Messages.erase(it);
        //then
        (*it)->folders.erase(&lhs);

        //but when do first step, it will also invalidate it
        //after lhs.Messages.erase(it);, *it is undefined
        //which is disaster in the second step!!!

        ++it;
    }
    */

    //so we use temp_set
    for(auto m_p : temp_set_lhs){
        m_p->remove(lhs);
    }


    //add tem_set_rhs {B,C,D,E} into lhs.Messages
    for(auto m_p : temp_set_rhs){
        m_p->save(lhs); //folders in Message add lhs, also lhs.Message insert m_p
    }

    //now process rhs, first remove B,C,D,E from rhs
    for(auto m_p : temp_set_rhs){
        m_p->remove(rhs);
    }

    //now add temp_set_lhs {A,B,C} to rhs.Messages
    for(auto m_p : temp_set_lhs){
        m_p->save(rhs);
    }
}