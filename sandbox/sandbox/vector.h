#pragma once

namespace Core {

template <class T>
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
    virtual Iterator& operator++() override
    {
        m_ptr++;
        return *this;
    }
    virtual Iterator operator++(int) override
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

// reverse iterator
template <class T>
class ReverseIterator : Iterator<T> {
public:
    ReverseIterator(Iterator<T>::pointer ptr)
        : Iterator<T>::m_ptr(ptr)
    {
    }

    virtual ReverseIterator& operator++() override
    {
        Iterator<T>::m_ptr--;
        return *this;
    }
    virtual ReverseIterator operator++(int) override
    {
        ReverseIterator tmp = *this;
        --(*this);
        return tmp;
    }
};

template <class T>
class Vector {
private:
    T* m_items = nullptr;
    T* m_begin = nullptr;
    T* m_end = nullptr;
    int m_size = 0;
    int m_capacity = 0;
    // int max_size = 0;

public:
    Vector(T* items, int size)
        : m_items(items)
        , m_begin(&items[0])
        , m_end(&items[m_size])
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

    //???
    T& Data()
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

    int Capacity()
    {
        return m_capacity;
    }

    void Clear()
    {
        delete[] m_items;
        m_items = nullptr;
        m_begin = nullptr;
        m_end = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    void PushBack(T value)
    {
        if (m_size + 1 > m_capacity) {
            m_capacity *= 2;
            ++m_size;
            T* items = new T[m_capacity];

            for (int i = 0; i < m_size; ++i) {
                items[i] = m_items[i];
            }

            delete[] m_items;
            m_items = items;
        } 

        m_items[m_size] = value;
    }

    // eh
    Iterator<T> Begin()
    {
        return Iterator(&m_begin);
    }

    Iterator<T> End()
    {
        return Iterator(&m_end);
    }

    // for tests

    T* GetItems()
    {
        return m_items;
    }

    void PrintItems()
    {
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_items[i] << std::endl;
        }
    }

    // to do
    T* At(T pos)
    {
        T* temp = nullptr;
        for (int i = 0; i < m_size; ++i) {
            if (&T[i] == T) {
                temp = T[i];
            }
        }

        return temp;
    }

    // operator[]
};

}