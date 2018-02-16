#ifndef MYUTIL_H
#define MYUTIL_H

#include <SDL.h>

class Projectile;

class MyUtil
{
public:
    static double deg(double);
    static double rad(double);
    static SDL_Point getVelocity(double, double, double, double);
    static bool checkCollision(Projectile*, Projectile*);

};

#endif /* MYUTIL_H */
