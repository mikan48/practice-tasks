#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

//template <typename T>

class Figure {
public:
	double area;

	virtual double GetArea() {
		//std::cout << area << std::endl;
		return area;
	};
	virtual void CalcArea() {}
};

class Rectangle : public Figure {
private:
	double h;
	double a;

public:
	double GetHigh() {
		return h;
	}

	double GetSide() {
		return a;
	}

	void SetHight(double h) {
		this->h = h;
	}

	void SetSide(double a) {
		this->a = a;
	}

	/*void SetParams(double h, double a) {
		this->a = a;
		this->h = h;
	}*/

	void CalcArea() override {
		this->area = h * a;
	}
};

class Circle : public Figure {
private:
	double r;
	
public:
	void SetRadius(double r) {
		this->r = r;
	}

	double GetRadius() {
		return r;
	}

	void CalcArea() override {
		this->area = pow(r, 2) * M_PI;
	}
};

class Triangle : public Figure {
private:
	double h;
	double a;

public:
	double GetHigh() {
		return h;
	}

	double GetSide() {
		return a;
	}

	void SetHight(double h) {
		this->h = h;
	}

	void SetSide(double a) {
		this->a = a;
	}


	void CalcArea() override {
		this->area = h * a / 2;
	}

	/*void foo() {
		std::cout << "foo" << std::endl;
	}*/
};