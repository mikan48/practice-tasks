#pragma once

namespace Core {

template <class T>
class Vector {
private:
    T* m_items = nullptr;
    T& m_begin;
    T& m_end;
    size_t m_size = 0;
    size_t m_capacity = 0;

public:
    class Iterator {

        using iterator_category = std::random_access_iterator_tag; // contiguous_iterator_tag
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        pointer m_ptr;

    public:
        Iterator(pointer ptr)
            : m_ptr(ptr)
        {
        }

        virtual ~Iterator()
        {
            delete m_ptr;
        }

        reference operator*() const
        {
            return *m_ptr;
        }
        pointer operator->()
        {
            return m_ptr;
        }
        virtual Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        virtual Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b)
        {
            return a.m_ptr == b.m_ptr;
        };
        friend bool operator!=(const Iterator& a, const Iterator& b)
        {
            return a.m_ptr != b.m_ptr;
        };
    };

    class ReverseIterator : Iterator {
    public:
        ReverseIterator(Iterator::pointer ptr)
            : Iterator::m_ptr(ptr)
        {
        }

        virtual ReverseIterator& operator++() override
        {
            Iterator::m_ptr--;
            return *this;
        }
        virtual ReverseIterator operator++(int) override
        {
            ReverseIterator tmp = *this;
            --(*this);
            return tmp;
        }
    };

    Vector(int size, T* items)
        : m_items(items)
        , m_begin(items[0])
        , m_end(items[m_size])
        , m_size(size)
        , m_capacity(size)
    {
    }

    Vector(int size)
        : m_size(size)
        , m_capacity(size)
    {
        m_items = new T[size];
    }

    Vector() = default;

    ~Vector()
    {
        delete[] m_items;
    }

    T& Front()
    {
        return m_begin;
    }

    T& Front() const
    {
        return m_begin;
    }

    T& Back()
    {
        return m_end;
    }

    T& Back() const
    {
        return m_end;
    }

    T* Data()
    {
        return m_begin;
    }

    bool Empty()
    {
        return m_size == 0;
    }

    int Size()
    {
        return m_size;
    }

    int Size() const
    {
        return m_size;
    }

    int Capacity()
    {
        return m_capacity;
    }

    int Capacity() const
    {
        return m_capacity;
    }

    void Clear()
    {
        delete[] m_items;
        m_items = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    // to do
    void PushBack(const T& value)
    {
        if (m_capacity == m_size) {
            Reserve(2 * m_size);
        }

        new (m_items + m_size) T(value);
        ++m_size;
    }

    void Reserve(size_t n)
    {
        if (n <= m_capacity)
            return;
        T* newItems = reinterpret_cast<T*>(new std::byte[n * sizeof(T)]);

        // std::unitialized_copy

        size_t i = 0;
        try {
            for (; i < m_size; ++i) {
                new (newItems + i) T(m_items[i]);
            }
        } catch (...) {
            for (size_t j = 0; j < i; ++j) {
                (m_items + i)->~T();
            }
            delete[] reinterpret_cast<std::byte*>(newItems);
            throw;
        }

        for (size_t i = 0; i < m_size; ++i) {
            m_items[i]->~T();
        }

        delete[] reinterpret_cast<std::byte*>(m_items);
        m_items = newItems;
        m_capacity = n;
    }

    void Resize(size_t n, const T& value = T())
    {
        if (n > m_capacity) {
            Reserve(n);
        }
        for (size_t i = m_size; i < n; ++i) {
            new (m_items + i) T(value);
        }
        if (n < m_size) {
            m_size = n;
        }
    }

    void PopBack()
    {
        --m_size;
        (m_items + m_size)->~T();
    }

    T& At(size_t pos)
    {
        if (pos >= m_size) {
            throw std::out_of_range();
        }

        return m_items[pos];
    }

    T& operator[](size_t pos)
    {
        return m_items[pos];
    }

    const T& operator[](size_t pos) const
    {
        return m_items[pos];
    }

    // eh
    Iterator Begin()
    {
        return Iterator(&m_begin);
    }

    Iterator End()
    {
        return Iterator(&m_end);
    }

    ReverseIterator RBegin()
    {
        return ReverseIterator(&m_begin);
    }

    ReverseIterator REnd()
    {
        return ReverseIterator(&m_end);
    }

};

}