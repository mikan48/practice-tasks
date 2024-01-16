#include "figures.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Figures {

double Figure::GetArea()
{
    return m_area;
}

bool Figure::AreaIsZero()
{
    if (m_area == 0) {
        std::cout << "Area is equal zero" << std::endl;
        return 1;
    } else {
        std::cout << "Area = " << m_area << std::endl;
        return 0;
    }
}

double Rectangle::GetHigh()
{
    return m_h;
}

double Rectangle::GetSide()
{
    return m_a;
}

void Rectangle::SetHight(double h)
{
    m_h = h;
}

void Rectangle::SetSide(double a)
{
    m_a = a;
}

void Rectangle::CalcArea()
{
    m_area = m_h * m_a;
}

void Circle::SetRadius(double r)
{
    m_r = r;

    CalcArea();
}

double Circle::GetRadius()
{
    return m_r;
}

void Circle::CalcArea()
{
    m_area = pow(m_r, 2) * M_PI;
}

double Triangle::GetHigh()
{
    return m_h;
}

double Triangle::GetSide()
{
    return m_a;
}

void Triangle::SetHight(double h)
{
    m_h = h;
}

void Triangle::SetSide(double a)
{
    m_a = a;
}

void Triangle::CalcArea()
{
    m_area = m_h * m_a / 2;
}

}