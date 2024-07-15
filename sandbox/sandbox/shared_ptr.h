#pragma once

namespace Core {

template <typename T>
class enabled_shared_from_this;

template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
private:

    struct BaseControlBlock {
        size_t shared_count = 0;
        size_t weak_count = 0;
        virtual T* GetObject() = 0;
        virtual ~BaseControlBlock() = default;
    };

    template <typename Allocator = std::allocator<T>>
    struct ControlBlockDirect : public BaseControlBlock {
        T* object = nullptr;

        ControlBlockDirect() = default;

        ControlBlockDirect(T* ptr)
            : object(ptr)
        {
        }

        T* GetObject() override
        {
            return object;
        }
    };

    struct ControlBlockMakeShared : public BaseControlBlock {
        alignas(T) std::byte* obj[sizeof(T)];

        T* GetObject() override
        {
            return reinterpret_cast<T*>(&obj);
        }
    };

    BaseControlBlock* m_cb = nullptr;

    template <typename U>
    friend class weak_ptr;

    struct make_shared_t { };

    template <typename U, typename Alloc, typename... Args>
    friend shared_ptr<U> allocate_shared(Alloc& alloc, Args&&... args);

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&... args);

    template <typename... Args>
    shared_ptr(make_shared_t, BaseControlBlock* storage_ptr, Args&&... args)
        : m_cb(storage_ptr)
    {
    }

    shared_ptr(ControlBlockMakeShared* cb)
        : m_cb(cb)
    {
        ++m_cb->shared_count;
    }

public:
    shared_ptr()
        : m_cb(new ControlBlockDirect())
    {
    }

    shared_ptr(T* ptr)
        : m_cb(new ControlBlockDirect(ptr))
    {
        if constexpr (std::is_base_of_v<enabled_shared_from_this<T>, T>) {
            m_cb->GetObject().cptr = *this; 
        }

        ++m_cb->shared_count;
    }

    shared_ptr(const shared_ptr& other)
        : m_cb(other.m_cb)
    {
        if (m_cb->GetObject() != nullptr) {
            ++(m_cb->shared_count);
        }
    }

    shared_ptr(shared_ptr&& other)
        : m_cb(other.m_cb)
    {
        m_cb = nullptr;
    }

    T& operator*() const
    {
        return *m_cb->GetObject();
    }

    T* operator->() const
    {
        return m_cb->GetObject();
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        m_cb = other.m_cb;

        if (m_cb->GetObject() != nullptr) {
            ++m_cb->shared_count;
        }

        return *this;
    }

    size_t use_count() const
    {
        return m_cb->shared_count;
    }

    T* get() const
    {
        return m_cb->GetObject();
    }

    ~shared_ptr()
    {
        --m_cb->shared_count;

        if (m_cb->shared_count > 0) {
            return;
        }
    }
};

template <typename T>
class weak_ptr {
public:
    typename shared_ptr<T>::BaseControlBlock* cptr = nullptr;

    weak_ptr(const shared_ptr<T>& ptr)
        : cptr(ptr.m_cb)
    {
        if (cptr->GetObject() != nullptr) {
            ++cptr->weak_count;
        }
    }

    bool expired() const
    {
        return cptr->shared_count == 0;
    }

    shared_ptr<T> lock() const
    {
        if (expired()) {
            return shared_ptr<T>();
        }

        return shared_ptr<T>(*this);
    }

    ~weak_ptr()
    {
        --cptr->weak_count;

        if (this->expired() && cptr->weak_count == 0) {
            delete cptr;
        }
    }
};

template <typename T>
class enabled_shared_from_this {
private:
    weak_ptr<T> m_wptr;

    template <typename U>
    friend class shared_ptr;

public:
    shared_ptr<T> shared_from_this() const
    {
        return m_wptr.lock();
    }
};

template <typename T, typename Alloc = std::allocator<T>, typename... Args>
shared_ptr<T> allocate_shared(Alloc& alloc, Args&&... args)
{
    auto cb = new typename shared_ptr<T>::ControlBlockMakeShared();
    std::allocator_traits<Alloc>::construct(alloc, cb->GetObject(), T(args...));

    shared_ptr<T> newShared(cb);

    return newShared;
}

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    auto alloc = std::allocator<T>();

    return allocate_shared<T>(alloc, std::forward<Args>(args)...);
}

}