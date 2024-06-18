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

    template <typename U, typename Alloc, typename... Args>
    friend shared_ptr<U> aloccate_shared(Alloc& alloc, Args&&... args);

    template <typename U, typename... Args>
    friend shared_ptr<T> make_shared(Args&... args);

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

    struct BaseControlBlock {
        size_t shared_count = 0;
        size_t weak_count = 0;
        virtual T* GetObject() = 0;
        virtual void SetObject(T* ptr) = 0;
        virtual ~BaseControlBlock() = default;
    };

    template <typename Deleter = std::default_delete<T>, typename Allocator = std::allocator<T>>
    struct ControlBlockDirect : public BaseControlBlock {
        T* object = nullptr;
        Deleter deleter;
        Allocator aloccator;

        ControlBlockDirect() = default;

        ControlBlockDirect(T* ptr)
            : object(ptr)
        {
        }

        T* GetObject() override
        {
            return object;
        }

        void SetObject(T* ptr) override
        {
            object = ptr;
        }
    };

    template <typename U, typename Allocator = std::allocator<T>>
    struct ControlBlockMakeShared : public BaseControlBlock {
        alignas(U) std::byte obj = new std::byte[sizeof(T)]; // to do
        Allocator allocator;
        // U object; // T* ptr

        T* GetObject() override
        {
            return static_cast<T*>(obj);
        }

        void SetObject(T* ptr) override
        {
            obj = static_cast<std::byte>(ptr);
        }
    };

    BaseControlBlock* m_cb = nullptr;

    /////////////////////

    // template <typename U>
    // struct ControlBlock {
    //    size_t shared_count = 0;
    //    size_t weak_count = 0;
    //    T* ptr = nullptr;
    //};

    // ControlBlock* m_cptr = nullptr;

    template <typename U>
    friend class weak_ptr;

    struct make_shared_t;

    template <typename... Args>
    shared_ptr(make_shared_t, BaseControlBlock* storage_ptr, Args&&... args)
        : m_cb(storage_ptr)
    {
    }

public:
    shared_ptr()
        : m_count(new size_t(0))
        , m_cb(new ControlBlockDirect())
    {
    }

    shared_ptr(T* ptr)
        : m_ptr(ptr)
        , m_count(new size_t(1))
        , m_cb(new ControlBlockDirect(ptr))
    {
        if constexpr (std::is_base_of_v<enabled_shared_from_this<T>, T>) {
            m_cb->GetObject().cptr = *this; //??
        }

        ++m_cb->shared_count;
    }

    shared_ptr(const shared_ptr& other)
        : m_cb(other.m_cb)
    {
        // m_cb->SetObject = other.m_cb->GetObject();

        if (m_cb->GetObject() != nullptr) { 
            ++(m_cb->shared_count);
        }
    }

    shared_ptr(shared_ptr&& other)
        : m_cb(other.m_cb)
    {
        m_cb = nullptr;
    }

    ///
    T& operator*() const
    {
        return *m_ptr;
    }

    T* operator->() const
    {
        return m_ptr;
    }
    ///

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
        // return m_ptr;
        // T obj = static_cast<T>(m_cb->GetObject()[0]);

        return m_cb->GetObject();
    }

    //~shared_ptr()
    //{
    //    if (m_count != nullptr && *m_count != 0) {
    //        --*m_count;

    //        if (*m_count > 0) {
    //            return;
    //        }
    //    }

    //    if (m_count == 0) {
    //        delete m_count;
    //    }
    //}

    ~shared_ptr()
    {
        --m_cb->shared_count;

        if (m_cb->shared_count > 0) {
            return;
        }

        if (m_cb->weak_count == 0) {
            delete m_cb;
            return;
        }

        // cptr->object.~T();
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

 template <typename T, typename Alloc = std::allocator<T>, typename... Args>
 shared_ptr<T> aloccate_shared(Alloc& alloc, Args&&... args)
{
     shared_ptr<T> shared;

     auto ptr = alloc.allocate(1);

     std::allocator_traits<Alloc>::construct(alloc, ptr, args...);

     return shared;
 }

template <typename T, typename... Args>
shared_ptr<T> make_shared(Args&&... args)
{
    auto alloc = std::allocator<T>();

    return aloccate_shared<T>(alloc, std::forward<Args>(args)...);

    // auto ptr = new typename shared_ptr<T>::ControlBlock { 1, T(std::forward<Args>(args)...) };
    // return shared_ptr<T>(shared_ptr<T>::make_shared_t(), ptr);

    //auto ptr = new T(std::forward<Args>(args)...);
    //return shared_ptr<T>(ptr);
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