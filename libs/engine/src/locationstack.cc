#include "locationstack.h"

namespace engine {

LocationStack::LocationStack()
{

}

LocationStack::~LocationStack()
{

}

void LocationStack::push(Point p)
{
    stack.push_back(p);
}

Point& LocationStack::pop()
{
    Point& p = stack.back();
    stack.pop_back();
    return p;
}

bool LocationStack::isEmpty()
{
    return stack.size() == 0;
}

void LocationStack::clear()
{
    stack.clear();
}

}
