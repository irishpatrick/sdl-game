#pragma once

#include <cstdio>
#include <vector>

#include "point.hpp"

namespace engine {

class LocationStack
{
public:
    LocationStack();
    ~LocationStack();

    void push(Point);
    Point& pop();
    bool isEmpty();
    void clear();

private:
    std::vector<Point> stack;
};

}
