#ifndef MISSILE_H
#define MISSILE_H

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <SDL.h>
#include "engine.h"
#include "projectile.h"

class Plane;

class Missile: public Projectile
{
public:
    Missile();
    ~Missile();

    void update(float);
    void launch();
    void setTarget(Plane*);

private:
    Plane* target;
    float target_angle;
};

#endif /* MISSILE_H */
