#include <iostream>
#include <vector>
#include <string>
#include <memory>

class StrBlob{
public:
    typedef std::vector<std::string>::size_type size_type;

    //constructor forward declaration
    StrBlob(); //default constructor
    StrBlob(std::initializer_list<std::string> il);

    //A constructor that can be called with a single argument defines an im- plicit conversion from the constructor’s parameter type to the class type,
    // if we use explicit, we cannot use = form, StrBlob b2 = {"a", "an", "the"}; not allowed, should be StrBlob b2( {"a", "an", "the"});

    //const member function to indicate the type *this is const
    //const objeact can only call const memeber function, 
    //if const member func return *this, *this will point to const object
    //then return type should be const reference 
    size_type size() const {return data->size();}

    bool empty() const {return data-> empty();}

    //add or remove elements member func
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();

    //element access member func
    std::string front();
    std::string front() const;

    std::string back();
    std::string back() const;

    std::shared_ptr<std::vector<std::string>> data;

private:
    //std::shared_ptr<std::vector<std::string>> data; //A default initialized smart pointer holds a null pointer

    //throw msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;

};

//constructor
//Initialize its data member to point to a dynamically allocated vector. 
//The default constructor allocates an empty vector:
StrBlob::StrBlob():data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il):data(std::make_shared<std::vector<std::string>>(il)){}

void StrBlob::check(size_type i, const std::string &msg) const {
        if (i >= data->size())
            throw std::out_of_range(msg);
}

std::string StrBlob::front(){
    // if the vector is empty,check will throw 
    check(0, "front on empty StrBlob");
    std::string result = "non-const version front: " + data->front();
    return result;
}

std::string StrBlob::front() const{
    // if the vector is empty,check will throw 
    check(0, "front on empty StrBlob"); 
    std::string result = "const version front: " + data->front();
    return result;
}

std::string StrBlob::back(){
    check(0, "back on empty StrBlob");
    std::string result = "non-const version back: " + data->back();
    return result;
}

std::string StrBlob::back() const{
    check(0, "back on empty StrBlob");
    std::string result = "const version back: " + data->back();
    return result;
}

void StrBlob::pop_back(){
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

int main()
{
    //==== ex 12.1 ====
    StrBlob b1; //b1 hold a shared_ptr p1 which point to empty vec1, p1 = &vec1;
    std::cout << b1.size() << std::endl; //0, check vec1.size()
    std::cout << b1.data.use_count() << std::endl; //1
    {
        StrBlob b2 = {"a", "an", "the"}; //b2 hold a shared_ptr p2 which point to vec2, p2 = &vec2
        std::cout << b1.size() << std::endl; //0, check vec1.size()
        std::cout << b2.size() << std::endl; //3, check vec2.size()
        std::cout << b1.data.use_count() << std::endl; //1, p1 is shared by obj b1
        std::cout << b2.data.use_count() << std::endl; //1, p2 is shared by obj b2
        b1 = b2; //when object copy, object member shared_ptr also copy
                // p1 = p2;
                // p1 address value change from &vec1 to &vec2, object vec1 reference count decrement from 1 to 0, vec1 destroyed, p1 = p2 = &vec2
                // now both p1 p2 point to vec2; object vec2 refenrence count increment from 1 to 2
                //so b1 b2 both contain the same memory part, this memory contain vec2
                // b1 and b2 object still has two different address, &b1, &b2 is different; just p1 and p2 are the same because the address value can be copyed
                //but the func cannot be copied
        std::cout << b1.size() << std::endl; //3, check vec2.size()
        std::cout << b2.size() << std::endl; //3, check vec2.size()
        std::cout << b1.data.use_count() << std::endl; //2, p2 shared by obj b1 and b2
        std::cout << b2.data.use_count() << std::endl; //2, p2 shared by obj b1 and b2
        b2.push_back("about"); // vec2.push_back()
        std::cout << b1.size() << std::endl; //4
        std::cout << b2.size() << std::endl; //4
        std::cout << b1.data.use_count() << std::endl; //2
        std::cout << b2.data.use_count() << std::endl; //2

        // b1 and b2 object still has two different address, &b1, &b2 is different; just p1 and p2 are the same because the address value can be copied
        // but the func cannot be copied
        //so b1 and b2 two different objects share the same part memory for their data member, data is a pointer address value, which can be copied
        std::cout << &b1 << std::endl; //0x16f3ff1f8
        std::cout << &b2 << std::endl; //0x16f3ff1d8
        std::cout << b1.data << std::endl; //0x141e05ed8
        std::cout << b2.data << std::endl; //0x141e05ed8
    }
    //b2 go out of scope, b2 destoyed, vec2 reference count decrement from 2 to 1

    //now b1 has its remaning elements except the one pointed by p1, which is the data member;
    std::cout << b1.size() << std::endl; //4
    std::cout << b1.data.use_count() << std::endl; //1, p2 shared only by b2

    //std::cout << b2.size() << std::endl; wrong, b2 is not in scope


    std::string s1 = b1.front(); //b1 is non-const object, it call both const and non-const member func,
    //when member func is overload, it will first choose non-const version
    std::cout << s1 << std::endl;
    std::cout << b1.back() << std::endl;
    //output
    // non-const version front: a
    // non-const version back: about

    const StrBlob obj_const({"aa", "bb"});
    std::cout << obj_const.front() << std::endl;
    std::cout << obj_const.back() << std::endl;
    //output
    // const version front: aa
    // const version back: bb

    const StrBlob b3; //empty vec, will throw error

    //b3 is const obj, it can only call const member function
    //so we need to add const overload version for below two

    std::string s3 = b3.back();
    std::cout << s3 << std::endl;
    std::string s4 = b3.front();
    std::cout << s4 << std::endl;
    //output will throw error since b3 has empty vec
    //libc++abi: terminating due to uncaught exception of type std::out_of_range: back on empty StrBlob

}