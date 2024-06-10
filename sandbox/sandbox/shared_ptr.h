#pragma once

namespace Core {

template <typename T>
class enabled_shared_from_this;

template <typename T>
class weak_ptr;

template <typename T>
class shared_ptr {
private:
    T* m_ptr = nullptr;
    size_t* m_count = nullptr;

    struct DeleterBase {
        virtual void operator()(void*);
        virtual ~DeleterBase() { }
    };

    template <typename U>
    struct DeleterDerived : public DeleterBase {
        U deleter;
        DeleterDerived(const U& deleter)
            : deleter(deleter)
        {
        }

        void operator()(void* ptr) override
        {
            deleter(ptr);
        }
    };

    DeleterBase* deleter = nullptr;

    //////////////////////

    // struct BaseControlBlock {
    //     size_t shared_count = 0;
    //     size_t weak_count = 0;
    //     virtual ~BaseControlBlock() = default;
    // };

    // template <typename Deleter = std::default_delete<T>, typename Allocator = std::allocator<T>>
    // struct ControlBlockDirect : BaseControlBlock {
    //     T* object;
    //     Deleter deleter;
    //     Allocator aloccator;
    //     //...
    // };

    // template <typename U, typename Allocator = std::allocator<T>>
    // struct ControlBlockMakeShared : BaseControlBlock {
    //     alignas(U) std::byte obj = new std::byte[sizeof(T)]; //to do
    //     Allocator allocator;
    //     //U object; // T* ptr
    // };

    // BaseControlBlock* m_cb;

    /////////////////////

    // template <typename U>
    struct ControlBlock {
        size_t shared_count = 0;
        size_t weak_count = 0;
        T* ptr = nullptr;
    };

    ControlBlock* m_cptr = nullptr;

    template <typename U>
    friend class weak_ptr;

    template <typename U, typename... Args>
    friend shared_ptr<T> make_shared(Args&... args);

    struct make_shared_t;

    template <typename... Args>
    shared_ptr(make_shared_t, ControlBlock* storage_ptr, Args&&... args)
        : m_cptr(storage_ptr)
    {
    }

public:
    shared_ptr()
        : m_count(new size_t(0))
        , m_cptr(new ControlBlock())
    {
    }

    shared_ptr(T* ptr)
        : m_ptr(ptr)
        , m_count(new size_t(1))
        , m_cptr(new ControlBlock())
    {
        if constexpr (std::is_base_of_v<enabled_shared_from_this<T>, T>) {
            m_cptr->object.cptr = *this; //??
        }

        ++m_cptr->shared_count;
        m_cptr->ptr = ptr;
    }

    shared_ptr(const shared_ptr& other)
        : m_cptr(other.m_cptr)
    {
        if (m_cptr->ptr != nullptr) {
            ++(m_cptr->shared_count);
        }
    }

    shared_ptr(shared_ptr&& other)
        : m_cptr(other.m_cptr)
    {
        m_cptr = nullptr;
    }

    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }

    shared_ptr& operator=(const shared_ptr& other)
    {
        m_cptr = other.m_cptr;

        if (m_cptr->ptr != nullptr) {
            ++m_cptr->shared_count;
        }

        return *this;
    }

    size_t use_count() const
    {
        return m_cptr->shared_count;
    }

    T* get() const
    {
        // return m_ptr;
        return m_cptr->ptr;
    }

    ~shared_ptr()
    {
        if (m_count != nullptr && *m_count != 0) {
            --*m_count;

            if (*m_count > 0) {
                return;
            }
        }

        if (m_count == 0) {
            delete m_count;
        }
    }

    //~shared_ptr()
    //{
    //    --m_cptr->shared_count;

    //    if (m_cptr->shared_count > 0) {
    //        return;
    //    }

    //    if (m_cptr->weak_count == 0) {
    //        delete cptr;
    //        return;
    //    }

    //    cptr->object.~T();
    //}
};

template <typename T>
class weak_ptr {
public:
    typename shared_ptr<T>::ControlBlock* cptr = nullptr;

    weak_ptr(const shared_ptr<T>& ptr)
        : cptr(ptr.m_cptr)
    {
    }

    bool expired() const
    {
        return cptr->shared_count > 0;
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
        if (cptr->shared_count == 0 && cptr->weak_count) {
            delete cptr;
        }
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    // return aloccate_shared(std::allocator<T>(), std::forward<Args>(args)...);

    auto ptr = new typename shared_ptr<T>::ControlBlock { 1, T(std::forward<Args>(args)...) };
    return shared_ptr<T>(shared_ptr<T>::make_shared_t(), ptr);

    // auto ptr = new T(std::forward<Args>(args)...);
    // return shared_ptr<T>(ptr);
}

template <typename T, typename Alloc, typename... Args>
shared_ptr<T> aloccate_shared(Alloc& alloc, Args&&... args)
{
    // rebind alloc to CBShared
    // alloc 1
    // placement new/construct obj
    // alloc to cb
}

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

}