#ifndef CONSTSTRBLOBPTR
#define CONSTSTRBLOBPTR
#include <string>
#include <vector>


class StrBlob;
//we want constStrBlobPtr point to const StrBlob object, which contain const vector<string>
//after constStrBlobPtr initilization, all member cannot change again!!!
//so no ++/--/=/+=/+/-
//only read
class constStrBlobPtr{
friend class StrBlob;
friend bool operator==(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs);
friend bool operator!=(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs);
public:
    constStrBlobPtr();//implicty initialize wptr to a nullptr, cannot change
    constStrBlobPtr(const StrBlob& a, size_t sz = 0);

    const std::string& operator[](std::size_t n) const;
    const std::string& operator*() const;
    const std::string* operator->() const;

private:
    std::shared_ptr<std::vector<std::string>>
    check(std::size_t, const std::string&) const;

    const std::size_t curr;
    const std::weak_ptr<std::vector<std::string>> wptr;
};

bool operator==(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs);
bool operator!=(const constStrBlobPtr& lhs, const constStrBlobPtr& rhs);

#endif