#include <memory>
#include <iostream>
#include <string>
#include <vector>
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

//==== end of class define ====

struct destination{
    std::string des;
    StrBlob des_bb1, des_bb2;// use default constructor
    std::vector<StrBlob> vec_des{des_bb1, des_bb2};
};

struct connection
{
    std::string con;
    StrBlob con_bb1, con_bb2;
    std::vector<StrBlob> vec_con{con_bb1, con_bb2};
};

connection connect(destination *p_des) //here p_des value same as &d, point to same memory
{
    p_des->des_bb1.data->push_back("receive signal");
    
    std::shared_ptr<connection> p_con = std::make_shared<connection>(); //default initilized a connection struct object in dynamic memory
    p_con->con_bb1.data->push_back("connected"); // p_con 0x156e05fd8, a diffrent memory
    return *p_con;
    //if use shared_ptr, when connect call finished, p_con destroyed, that dynamic memory freed, 
    //returned connection c is a new memory object, 0x16fdff198, which value is a copy of *p_con 
}

void disconnect(connection con)
{
    con.con_bb1.data->front() = "disconnected"; //change con_bb1 from connected to disconnected
}

//important part: use shared_ptr to manage own deletion code
    //if connection struct does not have default consturctor, 
    //then when disconnect(c) not run because of exception before it, c will not be destroyed and closed, memory leak
    //we should use a shard_ptr to manage disconnect(c)
    //so we use following two part to in place of previous disconnect(c); func
    void callable_destruct_on_c(connection* built_in_p)
    {
        //note the callable takes pointer that is type built-in pointer q, not type of shared_ptr
        disconnect(*built_in_p);
    }

void f(destination &d) //pass by reference
{
    //get a connection, remember to close it when done
    connection c = connect(&d); //d here has same memory as d1, d address 0x16fdff220
    //&c is 0x16fdff198

    //code part to use the connection

    //if there is a exception lead to exit f before call disconnect(c);
    //disconnect(c); //use to close and free c
    //no matter disconnect(c) runs or not run(when hit exception)
    //after this call finihsed object c 16fdff198 destroyed, 
    //this is becuase connection struct contains elements that all have default destructor


    //std::shared_ptr<connection> p_manage(&c, callable_destruct_on_c);
    //the lambda version of callbale_destruct_on_c
    std::shared_ptr<connection> p_manage(&c, [](connection *p){disconnect(*p);});
    //here we create a shared_ptr point to c;
    //no matter if there is exception in the code part to use the connection, after f(), p_manage out of scope
    //When p_manage is destroyed, it won’t execute delete on its stored pointer. Instead, p will call callable_destruct_on_c on that pointer. 
    //In turn, callable_destruct_on_c will call disconnect, thus ensuring that the connection is closed
    //if there is no exception, after this func, p_manage destroyed, it will still call callable_destruct_on_c, which will call disconenct(c)
    //note the callable takes pointer that is type built-in pointer q, not type of shared_ptr

    //syntax
    /*
    std::shared_ptr<T> p(q, d)
    p assumes ownership for the object to which the built-in pointer q points. 
    q must be convertible to T* (§ 4.11.2, p. 161). 
    p will use the callable object d (§ 10.3.2, p. 388) in place of delete to free q.
    */

    //let's make exception here, shared_ptr p_manage should be made right after creation of c, make sure it's created before exception
    int x = 3;
    if(x == 3){
        return; //here x = 3, it will return early, but the shared p_manage destroyed ensure the callable_destruct_on_c to disconnect(c)
    }
    //after this exception, it will not go to disconnect(c) below, but it will go to callable_destruct_on_c() because when share_ptr is out of scope, destroyed after this func, 
    //and it will call the deletion callable we defined

    //=====after process of c
    //disconnect(c)

}

int main()
{
    destination d1; // d1 default initialized, in d1, data use default constructor
    //after main(), d1 out of scope, inside d1 the dynamic memory for d1.des_bb1, des_bb2 will freed automatically
    //d1.des_bb1.data:0x157904178, des_bb2.data:0x1579041a8
    //&d1 is 0x16fdff220
    f(d1);

}
