#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include "sprite.h"

class Plane: public Sprite
{
public:
    Plane();
    ~Plane();

    void draw(SDL_Renderer*);

    float vx;
    float vy;
    float angle;
};

#endif /* PLANE_H */
