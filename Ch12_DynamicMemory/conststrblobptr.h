<<<<<<< HEAD
// ConstStrBlobPtr - pointer class to a const StrBlob
=======
// conststrblobptr.h -- 
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
#ifndef CONSTSTRBLOBPTR_H_
#define CONSTSTRBLOBPTR_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "strblob.h"


class ConstStrBlobPtr
{
public:
    ConstStrBlobPtr()
        : curr(0) { }
    ConstStrBlobPtr(const StrBlob& a, size_t sz=0)
        : wptr(a.data), curr(sz) { }

<<<<<<< HEAD
    const std::string& deref() const;   // dereference as const
    ConstStrBlobPtr& incr(); // prefix version
    bool operator==(const ConstStrBlobPtr& rhs)
        { return curr == rhs.curr; }
    bool operator!=(const ConstStrBlobPtr& rhs)
        { return curr != rhs.curr; }
=======
    const std::string& deref() const;
    ConstStrBlobPtr& incr(); // prefix version
    bool operator==(const ConstStrBlobPtr& rhs) const
        { return curr == rhs.curr; }
    bool operator!=(const ConstStrBlobPtr& rhs) const
        { return !(*this == rhs); }
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
private:
// check returns a shared_ptr to the vector if check succeeds
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;

<<<<<<< HEAD
    std::weak_ptr<std::vector<std::string>> wptr;     // constant reference;
    std::size_t curr;       // current position within the array
};

=======
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;       // current position within the array
};


>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
inline std::shared_ptr<std::vector<std::string>>
ConstStrBlobPtr::check(std::size_t i, const std::string& msg) const
{
    std::shared_ptr<std::vector<std::string>> ret = wptr.lock();
    if( !ret )
        throw std::runtime_error("unbount ConstStrBlobPtr");
    if( i >= ret->size() )
        throw std::out_of_range(msg);
    
    return ret;
}


inline const std::string& ConstStrBlobPtr::deref() const
{
    std::shared_ptr<std::vector<std::string>> p = check(curr, "dereference past end");
    return (*p)[curr];
}

// prefix: return a reference to the incremented object
inline ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
    // if curr already points past the end of the container can't increment it
<<<<<<< HEAD
    check(curr, "increment past end of StrBlobPtr");
=======
    check(curr, "increment past end of ConstStrBlobPtr");
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
    ++curr;
    return *this;
}

inline ConstStrBlobPtr StrBlob::cbegin() const
    { return ConstStrBlobPtr(*this); }
inline ConstStrBlobPtr StrBlob::cend() const
    { return ConstStrBlobPtr(*this, data->size()); }

<<<<<<< HEAD

=======
>>>>>>> 542e774ef888abf418964a6997031e98a15bf5f6
#endif /*CONSTSTRBLOBPTR_H_*/