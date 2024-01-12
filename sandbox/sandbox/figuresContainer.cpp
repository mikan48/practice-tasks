#include "figures.h"
#include <iostream>
#include <string>

namespace Container {

class FiguresContainer {
private:
	int m_maxSize = 0;
	
	Figures::Figure* m_figures/*[4] = {nullptr}*/ = nullptr;

	//using Figures = Figures::Figure*;

public:
	FiguresContainer(int size) : m_maxSize(size) 
	{
		
	}
	FiguresContainer(int size, Figures::Figure* figures) : m_maxSize(size)//, m_figures(figures) 
	{
		//Figures* figures = new Figures[size];

		//m_figures = new Figures::Figure[size];
		//m_figures = figures;

		for (int i = 0; i < size; i++) {
			//figures[i] = new Figures();
			/**m_figures[i] = figures[i];
			m_figures[i]->CalcArea();*/
			std::cout << m_figures[i].GetArea() << std::endl;
		}
	}
	/*FiguresContainer(const FiguresContainer& container) : m_size(container.m_size) 
	{
	}*/

	/*void AddFigures(Figures::Figure* figures) {
		
	}*/
};

}
