#include "figures.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Figures {

class Figure {
protected:
    double m_area = 0;

public:
    virtual double GetArea()
    {
        return m_area;
    };
    virtual void CalcArea() = 0;

    virtual ~Figure() {}
};

class Rectangle : public Figure {
private:
    double m_h = 0;
    double m_a = 0;

public:
    Rectangle(double high, double side) : m_h(high), m_a(side) {}
    Rectangle(const Rectangle& rectangle) : m_h(rectangle.m_h), m_a(rectangle.m_a) {}

    double GetHigh()
    {
        return m_h;
    }

    double GetSide()
    {
        return m_a;
    }

    void SetHight(double h)
    {
        m_h = h;
    }

    void SetSide(double a)
    {
        m_a = a;
    }

    void CalcArea() override
    {
        m_area = m_h * m_a;
    }
};

class Circle : public Figure {
private:
    double m_r = 0;

public:
    Circle(double radius) : m_r(radius) {}
    Circle(const Circle& circle) : m_r(circle.m_r) {}

    void SetRadius(double r)
    {
        m_r = r;
    }

    double GetRadius()
    {
        return m_r;
    }

    void CalcArea() override
    {
        m_area = pow(m_r, 2) * M_PI;
    }
};

class Triangle : public Figure {
private:
    double m_h = 0;
    double m_a = 0;

public:
    Triangle(double high, double side) : m_h(high), m_a(side) {}
    Triangle(const Triangle& triangle) : m_h(triangle.m_h), m_a(triangle.m_a) {}

    double GetHigh()
    {
        return m_h;
    }

    double GetSide()
    {
        return m_a;
    }

    void SetHight(double h)
    {
        m_h = h;
    }

    void SetSide(double a)
    {
        m_a = a;
    }

    void CalcArea() override
    {
        m_area = m_h * m_a / 2;
    }
};

}