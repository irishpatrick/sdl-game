#include <cmath>
#include <cstdio>
#include "myutil.h"
#include "config.h"
#include "projectile.h"

double MyUtil::rad(double d)
{
    return d * (M_PI / 180.0);
}

double MyUtil::deg(double r)
{
    return r * (180.0 / M_PI);
}

SDL_Point MyUtil::getVelocity(double xvel, double yvel, double force, double angle)
{
    SDL_Point vel = {0,0};

    double v = sqrt(pow(xvel,2) + pow(yvel,2));

    double c = 0.4;
    double a = 0.4;
    double p = 1.225;
    double drag = c * (p * pow(v,2)) / 2 * a;

    printf("FORCEDRAG: %f, %f\n", force, drag);

    vel.x = (sin(rad(angle)) * force) - (sin(rad(angle)) * drag);
    vel.y = (-cos(rad(angle)) * force) - (-cos(rad(angle)) * drag);

    return vel;
}

bool MyUtil::checkCollision(Projectile* a, Projectile* b)
{
    if (!a->solid || !b->solid)
    {
        return false;
    }

    if (
        a->x < b->x + b->w &&
        a->x + a->w > b->x &&
        a->y < b->y + b->h &&
        a->y + a->h > b->y
    )
    {
        return true;
    }

    return false;
}
