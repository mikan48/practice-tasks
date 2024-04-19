#pragma once

namespace Core {

template <typename T>
class shared_ptr {
private:
    T* m_ptr = nullptr;
    size_t* m_count = nullptr;

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

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    size_t use_count() const
    {
        return *count;
    }

    ~shared_ptr()
    {
        if (*m_count > 1) {
            --(*m_count);
            return;
        }
        delete m_ptr;
        delete m_count;
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&... args)
{
    auto ptr = new T(std::forward<Args>(args));
    return shared_ptr<T>(ptr);
}

}