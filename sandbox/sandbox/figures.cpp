#include "figures.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Figures {

class Figure {
protected:
    double m_area;

public:
    virtual double GetArea()
    {
        return m_area;
    };
    virtual void CalcArea() = 0;
};

class Rectangle : public Figure {
private:
    double m_h;
    double m_a;

public:
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
    double m_r;

public:
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
    double m_h;
    double m_a;

public:
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