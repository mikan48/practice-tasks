#include <iostream>
#include "figures.cpp"

void WrongInput(double& number) {

	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Wrong Input\n";

		std::cin >> number;
	}
}

int main() {
	Triangle triangle;
	Rectangle rectangle;
	Circle circle;

	double numb = 0;

	std::cout << "Input circle radius:\n";
	std::cin >> numb;

	WrongInput(numb);

	circle.SetRadius(numb);
	circle.CalcArea();
	std::cout << "Circle area:\n" << circle.GetArea() << std::endl;

	std::cout << "Input rectangle height:\n";
	std::cin >> numb;

	WrongInput(numb);

	rectangle.SetHight(numb);
	std::cout << "Input rectangle side:\n";
	std::cin >> numb;

	WrongInput(numb);

	rectangle.SetSide(numb);
	rectangle.CalcArea();
	std::cout << "Rectangle area:\n" << triangle.GetArea() << std::endl;

	std::cout << "Input triangle height:\n";
	std::cin >> numb;

	WrongInput(numb);

	triangle.SetHight(numb);

	std::cout << "Input triangle side:\n";
	std::cin >> numb;

	WrongInput(numb);

	triangle.SetSide(numb);
	triangle.CalcArea();
	std::cout << "Triangle area:\n" << triangle.GetArea() << std::endl;

	//std::cout << numb << std::endl;

	//Triangle t;
	//t.GetArea();
}

