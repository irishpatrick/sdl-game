#include "vec2.hpp"

namespace engine
{

    vec2::vec2() :
        x(0.0f),
        y(0.0f)
    {

    }

    vec2::~vec2()
    {

    }

    vec2 vec2::add(vec2 a, vec2 b)
    {
        vec2 c;
        c.x = a.x + b.x;
        c.y = a.y + b.y;

        return c;
    }

    vec2 vec2::scale(vec2 a, float f)
    {
        vec2 c;
        c.x = a.x * f;
        c.y = a.y * f;

        return c;
    }

    float vec2::dot(vec2 a, vec2 b)
    {
        float c;
        c = (a.x * a.y) + (b.x * b.y);

        return c;
    }
}