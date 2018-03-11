#ifndef POINT_H
#define POINT_H

namespace engine {

class Point
{
public:
    Point();
    Point(float, float);

    void Set(float, float);

    float x;
    float y;
};

}

#endif /* POINT_H */
