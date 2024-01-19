#ifndef CONTAINERS_H
#define CONTAINERS_H

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

    T* GetItems()
    {
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_items[i].GetArea() << std::endl;
        }

        return m_items;
    }

   /* void AddFigure(T* item);
    void DeleteFigure(T* item);
    double GetFiguresSumArea();*/
};

//class TriangleContainer {
//public:
//    TriangleContainer();
//    ~TriangleContainer();
//
//private:
//    Figures::Triangle triangles;
//};
//
//class RectangleContainer {
//public:
//    RectangleContainer();
//    ~RectangleContainer();
//
//private:
//    Figures::Rectangle rectangles;
//};

}

#endif
