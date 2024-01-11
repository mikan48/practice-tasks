#include <iostream>

//

template <class T>
class FiguresContainer {
private:
	const double m_size;
	FiguresContainer object1;
	FiguresContainer object2;
public:
	FiguresContainer(int elements) : m_size(elements*sizeof(T)) {}
	FiguresContainer(const FiguresContainer& container) : m_size(container.m_size) {}

	T& operator=(const T& other)
    {
        if (this != &other) 
        {
            if (size != other.size) 
            {
                data.reset(new int[other.size]);
                size = other.size;
            }
            std::copy(&other.data[0], &other.data[0] + size, &data[0]);
        }
        return *this;
	}

    /*void AddFigure(const T& item) {}
    void DeleteFigure(const T& item) {}
    double GetSumArea() {}

    ~FiguresContainer() {}*/
};

//class It {};
