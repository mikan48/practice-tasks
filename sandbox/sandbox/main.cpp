#include <iostream>
#include "figures.cpp"
#include "figuresContainer.cpp"

//void foo()
//{
//	
//}

int main() {
	Triangle triangle;
	Rectangle rectangle;
	Circle circle;

	double numb = 0;

	std::cout << "Input circle radius:\n";

	std::cin >> numb;

	/*while (std::cin.fail())
	{
		std::cin.clear();

		std::cout << "Wrong Input\n";

		std::cin >> numb;
	}*/

	circle.SetRadius(numb);
	circle.CalcArea();
	std::cout << "Circle area:\n" << circle.GetArea() << std::endl;


	std::cout << "Input rectangle height:\n";
	std::cin >> numb;
	rectangle.SetHight(numb);
	std::cout << "Input rectangle side:\n";
	std::cin >> numb;
	rectangle.SetSide(numb);
	rectangle.CalcArea();
	std::cout << "Rectangle area:\n" << triangle.GetArea() << std::endl;

	std::cout << "Input triangle height:\n";
	std::cin >> numb;
	triangle.SetHight(numb);
	std::cout << "Input triangle side:\n";
	std::cin >> numb;
	triangle.SetSide(numb);
	triangle.CalcArea();
	std::cout << "Triangle area:\n" << triangle.GetArea() << std::endl;

	//std::cout << numb << std::endl;

	//Triangle t;
	//t.GetArea();
}