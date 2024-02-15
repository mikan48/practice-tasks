#include <iostream>
#include <cassert>
#include "figures.h"
#include "containers.h"
#include "vector.h"
#include "vector"

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

void ContainersAndFunctionTest() 
{
	Figures::Circle* circle = new Figures::Circle(2);
	AreaIsZero(circle);
	std::cout << std::endl;

	Figures::Circle* circles = new Figures::Circle[3] { Figures::Circle(1), Figures::Circle(5), Figures::Circle(11) };
	for (int i = 0; i < 3; ++i) {
		AreaIsZero(&circles[i]);
	}

	std::cout << std::endl << std::endl << std::endl;

	//circle container
	Containers::CircleContainer* circlesContainer = new Containers::CircleContainer(3, circles);
	circlesContainer->PrintCircles();
	std::cout << std::endl;
	circlesContainer->AddFigure(Figures::Circle(1));
	circlesContainer->PrintCircles();
	std::cout << "Sum area: " << circlesContainer->GetFiguresSumArea() << std::endl;
	std::cout << std::endl;
	circlesContainer->DeleteFigure(&circlesContainer->GetItems()[1]);
	circlesContainer->PrintCircles();

	std::cout << std::endl << std::endl << std::endl;
	
	//template
	Containers::Container<Figures::Circle> container(3, new Figures::Circle[3] { Figures::Circle(1), Figures::Circle(5), Figures::Circle(11) });
	container.AddFigure(Figures::Circle(1));
	container.PrintItems();
	std::cout << "Sum area: " << container.GetFiguresSumArea() << std::endl;
	container.DeleteFigure(&container.GetItems()[1]);
	container.PrintItems();

	std::cout << std::endl << "Triangles"  << std::endl;
	Containers::Container<Figures::Triangle> trianglesContainer(2, new Figures::Triangle[2] { Figures::Triangle(1, 1), Figures::Triangle(5, 4) });
	trianglesContainer.PrintItems();
	std::cout << "Sum area: " << trianglesContainer.GetFiguresSumArea() << std::endl;

	delete circle;
	delete circlesContainer;
}

int main() 
{
	//FiguresFeaturesTest();
	//ContainersAndFunctionTest();

	//Figures::Circle* circles = new Figures::Circle[3] { Figures::Circle(1), Figures::Circle(5), Figures::Circle(11) };

	//Core::Vector<int> vector(3, new int[3] {3, 5, 6} );
	Core::Vector<int> vector = {3, 5, 6};
	Core::Vector<int> emptyVector;
	assert(emptyVector.Empty() == true);
	std::cout << vector.Empty() << std::endl;
	assert(vector.Empty() == false);

	std::cout << "Capacity: " << vector.Capacity() << std::endl;
	assert(vector.Capacity() == 3);
	vector.PushBack(18);
	assert(vector.Capacity() == 6);
	std::cout << "Capacity: " << vector.Capacity() << std::endl;
	vector.PopBack();
	std::cout << vector.Size() << " end." << std::endl;
	assert(vector.Size() == 3);

	auto iter = vector.Begin();

	vector.PushBack(18);

	while (iter != vector.End()) {
		std::cout << "vector: " << *iter << std::endl;
		++iter;
	}

	vector.ShrinkToFit();
	std::cout << "Capacity: " << vector.Capacity() << std::endl;

	vector.At(1);
	vector.Data();
	vector.Front();
	vector.Back();
	

	vector.Clear();
	assert(vector.Empty() == true);
	assert(vector.Size() == 0);
	std::cout << vector.Empty() << std::endl;
	
	std::cout << vector.Size() << std::endl;

	/*std::vector<int> vec;
	vec[0];*/

	return 0;
}

