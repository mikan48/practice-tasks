#pragma once

namespace Core {

template <typename T>
class shared_ptr {
private:
    T* m_ptr = nullptr;
    size_t* m_count = nullptr;

    template <typename U>
    struct ControlBlock {
        size_t shared_count;
        size_t weak_count;
        U object;
    };

    template <typename U>
    class weak_ptr;

    ControlBlock<T>* m_cptr = nullptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&&... args);

    struct make_shared_t;

    template <typename... Args>
    shared_ptr(make_shared_t, ControlBlock<T>* storage_ptr, Args&&... args)
        : m_cptr(storage_ptr)
    {
    }

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
        --m_cptr->shared_count;

        if (m_cptr->shared_count > 0) {
            return;
        }

        if (m_cptr->weak_count == 0) {
            delete cptr;
            return;
        }

        cptr->object.~T();
    }
};

template <typename T>
class weak_ptr {
    ControlBlock<T>* m_cptr = nullptr;

public:
    weak_ptr(const shared_ptr<T>& ptr)
        : m_cptr(ptr.m_cptr)
    {
    }

    bool expired() const
    {
        return m_cptr->shared_count > 0;
    }

    shared_ptr<T> lock() const
    {
    }

    ~weak_ptr()
    {
        
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&... args)
{
    auto ptr = new ControlBlock<T> { 1, T(std::forward<Args>(args)...) };
    return shared_ptr<T>(shared_ptr::make_shared_t(), ptr);

    // auto ptr = new T(std::forward<Args>(args));
    // return shared_ptr<T>(ptr);
}

}