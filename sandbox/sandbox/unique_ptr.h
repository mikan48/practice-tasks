#pragma once

namespace Core {

template <typename T>
class unique_ptr {
private:
    T* ptr;

public:
    explicit unique_ptr(T* ptr)
        : ptr(ptr)
    {
    }

    ~unique_ptr()
    {
        delete ptr;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& another) : ptr(another.ptr)
    { 
        another.ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& another) 
    {
        delete ptr;
        ptr = another.ptr;
        another.ptr = nullptr;
    }

    T& operator*() const
    {
        return *ptr;
    }

    T* operator->() const
    {
        return ptr;
    }
};

}