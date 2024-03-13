#pragma once

namespace Core {

template <typename T>
class unique_ptr {
private:
    T* m_ptr = nullptr;

public:
    explicit unique_ptr(T* ptr)
        : m_ptr(ptr)
    {
    }

    unique_ptr() = default;

    ~unique_ptr()
    {
        delete m_ptr;
    }

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;

    unique_ptr(unique_ptr&& another)
        : m_ptr(another.m_ptr)
    {
        another.m_ptr = nullptr;
    }

    unique_ptr& operator=(unique_ptr&& another)
    {
        delete m_ptr;
        m_ptr = another.m_ptr;
        another.m_ptr = nullptr;
        return *this;
    }

    T* get()
    {
        return m_ptr;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }
};

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args)
{
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}

}