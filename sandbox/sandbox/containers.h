#ifndef CONTAINERS_H
#define CONTAINERS_H

#include "figures.h"

namespace Containers {

//class Container {
//public:
//    Container();
//    ~Container();
//
//private:
//};

class CircleContainer /*: Container*/ {
public:
    CircleContainer();
    ~CircleContainer();

private:
    Figures::Circle circles;
};

class TriangleContainer {
public:
    TriangleContainer();
    ~TriangleContainer();

private:
    Figures::Triangle triangles;
};

class RectangleContainer {
public:
    RectangleContainer();
    ~RectangleContainer();

private:
    Figures::Rectangle rectangles;
};

}

#endif
