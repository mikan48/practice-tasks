#pragma once

#include "figures.h"

#include <iostream>

namespace Containers {

class CircleContainer {
private:
    Figures::Circle* m_items = nullptr;
    int m_size = 0;

public:
    CircleContainer(int size);
    CircleContainer(int size, Figures::Circle* circles);

    void AddFigure(Figures::Circle item);

    Figures::Circle* GetItems();

    double GetFiguresSumArea();

    void DeleteFigure(Figures::Circle* item);
    void PrintCircles();

    ~CircleContainer();
};

template <class T>
class Container {
private:
    T* m_items;
    int m_size = 0;

public:
    Container(int size)
        : m_size(size)
    {
        m_items = new T[size];
    }
    Container(int size, T* items)
        : m_size(size)
        , m_items(items)
    {
    }

    ~Container() 
    {
        delete[] m_items;
    }

    T* GetItems()
    {
        return m_items;
    }

    void AddFigure(T item)
    {
        T* items = new T[m_size + 1];

        for (int i = 0; i < m_size; ++i) {
            items[i] = m_items[i];
        }
        items[m_size] = item;

        ++m_size;
        delete[] m_items;
        m_items = items;
        
    }

    void DeleteFigure(T* item)
    {
        T* items = new T[m_size - 1];
        bool isDeleted = false;
        int k = 0;

        for (int i = 0; i < m_size; ++i) {
            if (&m_items[i] != item) {
                items[k] = m_items[i];
                ++k;
            } else {
                isDeleted = true;
            }
        }

        if (isDeleted) {
            --m_size;
            delete[] m_items;
            m_items = items;
        } else {
            delete[] items;
        }
        
    }

    double GetFiguresSumArea()
    {
        double area = 0;

        for (int i = 0; i < m_size; ++i) {
            area += m_items[i].GetArea();
        }

        return area;
    }

    void PrintItems()
    {
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_items[i].GetArea() << std::endl;
        }
    }
};


}
