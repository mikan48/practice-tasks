
class Figure {
protected:
    double m_area;

public: 
    virtual double GetArea();
    virtual void CalcArea();
};

class Rectangle : public Figure {
private:
    double m_h;
    double m_a;

public:
    double GetHigh();
    double GetSide();
    void SetHight(double h);
    void SetSide(double a);
};

class Circle : public Figure {
private:
    double m_r;

public:
    void SetRadius(double r);
    double GetRadius();
};

class Triangle : public Figure {
private:
    double m_h;
    double m_a;

public:
    double GetHigh();
    double GetSide();
    void SetHight(double h);
    void SetSide(double a);
};