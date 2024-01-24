#pragma once

namespace Figures {

class Figure {
protected:
    double m_area = 0;

public:
    virtual double GetArea();
    virtual void CalcArea() = 0;
    virtual ~Figure() {};
};

class Rectangle : public Figure {
private:
    double m_h = 0;
    double m_a = 0;

public:
    Rectangle() = default;
    Rectangle(double high, double side);
    Rectangle(const Rectangle& rectangle)
        : m_h(rectangle.m_h)
        , m_a(rectangle.m_a)
    {
    }

    virtual void CalcArea() override;

    double GetHigh();
    double GetSide();
    void SetHight(double h);
    void SetSide(double a);
};

class Circle : public Figure {
private:
    double m_r = 0;

public:
    Circle() = default;
    Circle(double radius);
    Circle(const Circle& circle)
        : m_r(circle.m_r)
    {
    }

    virtual void CalcArea() override;

    void SetRadius(double r);
    double GetRadius();
};

class Triangle : public Figure {
private:
    double m_h = 0;
    double m_a = 0;

public:
    Triangle() = default;
    Triangle(double high, double side);
    Triangle(const Triangle& triangle)
        : m_h(triangle.m_h)
        , m_a(triangle.m_a)
    {
    }

    virtual void CalcArea() override;

    double GetHigh();
    double GetSide();
    void SetHight(double h);
    void SetSide(double a);
};
}

