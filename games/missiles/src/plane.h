#ifndef PLANE_H
#define PLANE_H

#include "engine.h"
#include "projectile.h"

class Plane: public Projectile
{
public:
    Plane();
    ~Plane();

    float max_speed;
};

#endif /* PLANE_H */
