#ifndef LOCATIONSTACK_H
#define LOCATIONSTACK_H

#include <cstdio>
#include <vector>

#include "point.h"

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

#endif /* LOCATIONSTACK_H */
