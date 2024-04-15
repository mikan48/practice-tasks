#pragma once

namespace Core {

template <typename T>
class shared_ptr {
private:
    T* m_ptr;
    size_t* m_count;

public:
    shared_ptr() { }

    shared_ptr(T* ptr)
        : ptr(ptr)
        , m_count(new size_t(1))
    {
    }

    shared_ptr(const shared_ptr& other)
        : m_ptr(other.m_ptr)
        , m_count(other.m_count)
    {
        ++(*m_count);
    }

    shared_ptr(shared_ptr&& other)
        : m_ptr(other.m_ptr)
        , m_count(other.m_count)
    {
        other.m_ptr = nullptr;
        other.m_count = nullptr;
    }
};
}