#pragma once

namespace Core {

template <typename T>
class Vector {
private:
    T* m_items = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;

public:
    class Iterator {
    public:
        using iterator_category = std::random_access_iterator_tag; // contiguous_iterator_tag
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

    private:
        pointer m_ptr;

    public:
        Iterator(pointer ptr)
            : m_ptr(ptr)
        {
        }

        reference operator*() const
        {
            return *m_ptr;
        }
        pointer operator->()
        {
            return m_ptr;
        }
        Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }
        Iterator operator++(int)
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

    Vector(size_t size)
        : m_size(size)
        , m_capacity(size)
    {
        m_items = reinterpret_cast<T*>(new std::byte[size * sizeof(T)]);
    }

    Vector(std::initializer_list<T> list)
    {
        m_items = reinterpret_cast<T*>(new std::byte[list.size() * sizeof(T)]);
        auto iterator = list.begin();
        for (size_t i = 0; i < list.size(); ++i) {
            new (m_items + i) T(*iterator);
            ++iterator;
        }
        m_size = list.size();
        m_capacity = m_size;
    }

    Vector() = default;

    ~Vector()
    {
        delete[] reinterpret_cast<std::byte*>(m_items);
    }

    T& Front() const
    {
        return &m_items[0];
    }

    T& Back() const
    {
        return &m_items[m_size];
    }

    T* Data()
    {
        return &m_items[0];
    }

    const T* Data() const
    {
        return &m_items[0];
    }

    bool Empty() const
    {
        return m_size == 0;
    }

    size_t Size() const
    {
        return m_size;
    }

    size_t Capacity() const
    {
        return m_capacity;
    }

    void Clear()
    {
        for (size_t i = 0; i < m_size; ++i) {
            (m_items + i)->~T();
        }
        delete[] reinterpret_cast<std::byte*>(m_items);
        m_items = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    void PushBack(const T& value)
    {
        if (m_capacity == m_size) {
            if (m_size != 0) {
                Reserve(2 * m_size);
            } else {
                Reserve(1);
            }
        }

        new (m_items + m_size) T(value);
        ++m_size;
    }

    void Reserve(size_t n)
    {
        if (n <= m_capacity) {
            return;
        }
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

        for (size_t j = 0; j < m_size; ++j) {
            m_items[j].~T();
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
            throw std::out_of_range("out of range");
        }

        return m_items[pos];
    }

    const T& At(size_t pos) const
    {
        if (pos >= m_size) {
            throw std::out_of_range("out of range");
        }

        return m_items[pos];
    }

    void ShrinkToFit()
    {
        if (m_capacity == m_size) {
            return;
        }

        T* newItems = reinterpret_cast<T*>(new std::byte[m_size * sizeof(T)]);

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

        for (size_t j = 0; j < m_size; ++j) {
            m_items[j].~T();
        }

        delete[] reinterpret_cast<std::byte*>(m_items);
        m_items = newItems;
        m_capacity = m_size;
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
        return Iterator(&m_items[0]);
    }

    Iterator End()
    {
        return Iterator(&m_items[m_size]);
    }

    /*ReverseIterator RBegin()
    {
        return ReverseIterator(&m_begin);
    }

    ReverseIterator REnd()
    {
        return ReverseIterator(&m_end);
    }*/
};

}