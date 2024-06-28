template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
    List<elemType>();
    List<elemType>(const List<elemType> & orig);
    List<elemType>& operator=(const List<elemType>& rhs);
    ~List();

    //Inside the scope of the class template itself, we may use the name of the template without arguments:
    //so here is inside scope of class template List
    //we can use List or List<elemType> inside List::
    //but here ListItem is not inside class template ListItem:: scope
    //we cannot simply use ListItem inside class template List
    //we must use ListItem<elemType>, which here elemType (paramter for class template List) is argument for class Template ListItem
    void insert(ListItem<elemType> *ptr, elemType value);
private:
    ListItem<elemType> *front, *end;

};
/**
template <typename elemType> class ListItem{
friend class List<elemType>; //List::insert() need to access ListItem private member
public:
    ListItem():v(elemType()), next(nullptr){} //same as ListItem<elemType>():v(elemType()){}, inside class <elemType> can be not applied, compiler will apply <elemType>, here use elemType default constructor elemType()
    ListItem(elemType v_p):v(v_p), next(nullptr){}
    ListItem(const ListItem& orig){
        v = orig.v; //this will call elemType own copy constructor
        if(orig.next != nullptr){
            next = new ListItem(*(orig.next));
        } else next = nullptr;
    }
    ListItem& operator=(const ListItem& rhs){

        if(this != &rhs){
            v = rhs.v; //use elemType own copy assignment
            delete next;
            if (rhs.next != nullptr){
                next = new ListItem(*(rhs.next));
            } else next = nullptr;
        }
        //this = &rhs, do nothing
        return *this;   
    }

private:
    elemType v;
    ListItem<elemType>* next;

};

template<typename elemType>
List<elemType>::List():front(nullptr), end(nullptr){}

template<typename elemType>
List<elemType>::List(const List<elemType>& orig){
    front = new ListItem<elemType> (*(orig.front));
    end = new ListItem<elemType> (*(orig.end));
}

template<typename elemType>
List<elemType>& List<elemType>::operator=(const List<elemType>& rhs){
    if(this != &rhs){
        //free old this
        delete front;
        delete end;

        front = new ListItem<elemType> (*(rhs.front));
        end = new ListItem<elemType> (*(rhs.end));

        auto curr = front;
        while(curr->next != nullptr){
            curr = curr->next;
        }
        //now curr is the last ListItem inside front, curr->next = nullptr;
        curr->next = end; //link front and end
    }
    return *this;
}

template<typename elemType>
List<elemType>::~List(){
    delete front;
    delete end;
    front = nullptr;
    end = nullptr;
}

template<typename elemType>
void List<elemType>::insert(ListItem<elemType> *ptr, elemType value){
    
}
*/
