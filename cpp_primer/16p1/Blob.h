#ifndef BLOB
#define BLOB

#include <memory>
#include <vector>
#include <string>
template<typename T>
class BlobPtr;

template<typename T>
class Blob{
friend class BlobPtr<T>;
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    //here typename to tell the compiler size_type is a type, not class template
    Blob();
    Blob(std::initializer_list<T> il);
    template <typename IT>Blob(IT b, IT e);
    Blob(const Blob& orig);
    Blob& operator=(const Blob& rhs);

    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const T& t) {data->push_back(t);}
    void push_back(T&& t) {data->push_back(std::move(t));}
    void pop_back();

    T& back();
    const T& back() const;

    T& operator[](size_type i);
    const T& operator[](size_type i) const;

    T& front();
    const T& front() const;

private:
    std::shared_ptr<std::vector<T>> data;
    void check(size_type i, const std::string& msg) const;
};



template<typename T>
Blob<T>::Blob():data(std::make_shared<std::vector<T>>()){}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il):data(std::make_shared<std::vector<T>>(il)){}

// template<typename T>
// Blob<T>::Blob(const Blob<T>& orig):data(new std::vector<T>(*(orig.data))){}

template<typename T>
template <typename IT>
Blob<T>::Blob(IT b, IT e):data(std::make_shared<std::vector<T>>(b, e)){}

template<typename T>
Blob<T>::Blob(const Blob<T>& orig){
    data = orig.data;
}

template<typename T>
Blob<T>& Blob<T>::operator=(const Blob<T>& rhs){
    data = rhs.data;
    return *this;
}

template<typename T>
void Blob<T>::check(size_type i, const std::string& msg) const{
    if(i >= size()){
        throw std::out_of_range(msg);
    }
}

template<typename T>
void Blob<T>::pop_back(){
    check(0, "pop_back() on empty vector");
    data->pop_back();
}

template<typename T>
T& Blob<T>::back(){
    check(0, "back() on empty vector");
    return data->back();
}

template<typename T>
const T& Blob<T>::back() const{
    check(0, "back() on empty vector");
    return data->back();
}

template<typename T>
T& Blob<T>::front(){
    check(0, "front() on empty vector");
    return data->front();
}

template<typename T>
const T& Blob<T>::front() const{
    check(0, "front() on empty vector");
    return data->front();
}

template<typename T>
T& Blob<T>::operator[](size_type i){
    check(i, "subscript out of vector");
    return (*data)[i];
}

template<typename T>
const T& Blob<T>::operator[](size_type i) const{
    check(i, "subscript out of vector");
    return (*data)[i];
}

#endif