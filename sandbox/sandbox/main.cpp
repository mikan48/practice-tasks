#include <iostream>
#include "figures.h"

void WaitingForCorrectInput(double& number) 
{
	while (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Wrong Input\n";

		std::cin >> number;
	}
}

void FiguresFeaturesTest() 
{
	Figures::Triangle triangle;
	Figures::Rectangle rectangle;
	Figures::Circle circle;

	double numb = 0;

	std::cout << "Input circle radius:\n";
	std::cin >> numb;

	WaitingForCorrectInput(numb);

	circle.SetRadius(numb);
	circle.CalcArea();
	std::cout << "Circle area:\n" << circle.GetArea() << std::endl;

	std::cout << "Input rectangle height:\n";
	std::cin >> numb;

	WaitingForCorrectInput(numb);

	rectangle.SetHight(numb);
	std::cout << "Input rectangle side:\n";
	std::cin >> numb;

	WaitingForCorrectInput(numb);

	rectangle.SetSide(numb);
	rectangle.CalcArea();
	std::cout << "Rectangle area:\n" << rectangle.GetArea() << std::endl;

	std::cout << "Input triangle height:\n";
	std::cin >> numb;

	WaitingForCorrectInput(numb);

	triangle.SetHight(numb);

	std::cout << "Input triangle side:\n";
	std::cin >> numb;

	WaitingForCorrectInput(numb);

	triangle.SetSide(numb);
	triangle.CalcArea();
	std::cout << "Triangle area:\n" << triangle.GetArea() << std::endl;
}

bool AreaIsZero(Figures::Figure* figure)
{
    if (figure->GetArea() == 0) {
        std::cout << "Area is equal zero" << std::endl;

        return true;
    } else {
        std::cout << "Area = " << figure->GetArea() << std::endl;

        return false;
    }
}

int main() 
{
	//FiguresFeaturesTest();

	Figures::Circle* circle = new Figures::Circle(2);
	circle->CalcArea();
	AreaIsZero(circle);

	/*int numb = 5;

	Figures::Figure** figures = new Figures::Figure*[numb];

	for(int i = 0; i < numb; ++i) {
		std::cout << figures[i]->AreaIsZero() << std::endl;
	}*/

	/*auto figures2 = std::make_unique<Figures::Figure[]>(new Figures::Figure[numb]);
	for(int i = 0; i < numb; i++) {
		std::cout << figures2[i].get() << std::endl;
	}*/
}

