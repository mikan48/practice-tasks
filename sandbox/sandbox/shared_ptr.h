#pragma once

namespace Core {

template <typename T>
class enabled_shared_from_this;

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
    //     alignas(U) std::byte[sizeof(T)] obj; //to do
    //     Allocator allocator;
    //     U object; // T* ptr
    // };

    // BaseControlBlock* m_cb;

    /////////////////////

    template <typename U>
    struct ControlBlock {
        size_t shared_count = 0;
        size_t weak_count = 0;
        U object;
    };

    template <typename U>
    friend class weak_ptr;

    ControlBlock<T>* m_cptr = nullptr;

    template <typename U, typename... Args>
    friend shared_ptr<U> make_shared(Args&... args);

    struct make_shared_t;

    template <typename... Args>
    shared_ptr(make_shared_t, ControlBlock<T>* storage_ptr, Args&&... args)
        : m_cptr(storage_ptr)
    {
    }

public:
    shared_ptr()
        : m_count(new size_t(0))
    {
    }

    shared_ptr(T* ptr)
        : m_ptr(ptr)
        , m_count(new size_t(1))
    {
        if constexpr (std::is_base_of_v<enabled_shared_from_this<T>, T>) {
            m_cptr->object.cptr = *this; //??
        }
    }

    shared_ptr(const shared_ptr& other)
        : m_ptr(other.m_ptr)
        , m_count(other.m_count)
    {
        if (m_ptr != nullptr) {
            ++(*m_count);
        }
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
    
    shared_ptr& operator=(const shared_ptr& other)
    {
        m_count = other.m_count;
        m_cptr = other.m_cptr;
        m_ptr = other.m_ptr;
        deleter = other.deleter;

        if (m_ptr != nullptr) {
            m_count++;
        }

        return *this;
    }

    size_t use_count() const
    {
        return *m_count;
    }

    T* get() const
    {
        return m_ptr;
        // return m_cptr->object*;
    }

    ~shared_ptr()
    {
        if(m_count != nullptr && *m_count != 0) {
            --*m_count;

            if (*m_count > 0) {
            return;
            }
        }        

        if(m_count == 0) {
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
    shared_ptr::ControlBlock<T>* cptr = nullptr;

    weak_ptr(const shared_ptr<T>& ptr)
        : cptr(ptr.cptr)
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
            delete cptr->shared_count;
            delete cptr->weak_count;
        }
    }
};

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&... args)
{
    return aloccate_shared(std::allocator<T>(), std::forward<Args>(args)...);
    // auto ptr = new ControlBlock<T> { 1, T(std::forward<Args>(args)...) };
    // return shared_ptr<T>(shared_ptr::make_shared_t(), ptr);

    // auto ptr = new T(std::forward<Args>(args));
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