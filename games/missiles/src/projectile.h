#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "engine.h"

class Projectile: public Sprite
{
public:
    Projectile();
    virtual ~Projectile();

    virtual void update(float);
    virtual void draw(SDL_Renderer*);
    virtual void setCamera(Camera*);

    float vx;
    float vy;
    float angle;
    float thrust;

protected:
    Camera* camera;
};

#endif /* PROJECTILE_H */
