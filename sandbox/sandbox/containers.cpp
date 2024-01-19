#include "containers.h"

#include <iostream>

namespace Containers {

CircleContainer::CircleContainer(int size)
    : m_size(size)
{
    m_items = new Figures::Circle[size];
}
CircleContainer::CircleContainer(int size, Figures::Circle* circles)
    : m_size(size)
    , m_items(circles)
{
}

void CircleContainer::AddFigure(Figures::Circle item)
{
    Figures::Circle* circles = new Figures::Circle[m_size + 1];

    for (int i = 0; i < m_size; ++i) {
        circles[i] = m_items[i];
    }
    circles[m_size] = item;
    ++m_size;
    m_items = circles;
}

Figures::Circle* CircleContainer::GetItems()
{
    return m_items;
}

double CircleContainer::GetFiguresSumArea()
{
    double area = 0;

    for (int i = 0; i < m_size; ++i) {
        area += m_items[i].GetArea();
    }

    return area;
}

void CircleContainer::DeleteFigure(Figures::Circle* item) 
{
    Figures::Circle* circles = new Figures::Circle[m_size - 1];
    bool IsDeleted = false;
    int k = 0;

    for (int i = 0; i < m_size; ++i) {
        if (&m_items[i] != item) {
            circles[k] = m_items[i];
            ++k;
        } else {
            IsDeleted = true;
        }
    }

    if(IsDeleted) {
        --m_size;
        m_items = circles;    
    }
}

void CircleContainer::PrintCircles()
{
    for (int i = 0; i < m_size; ++i) {
        std::cout << m_items[i].GetArea() << std::endl;
    }
}

}