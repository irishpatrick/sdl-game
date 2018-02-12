#ifndef MISSILE_H
#define MISSILE_H

#include <SDL.h>
#include "engine.h"

class Missile: public Sprite
{
public:
    Missile();
    ~Missile();

    void update(float);
    void draw(SDL_Renderer*);
    void setCamera(Camera*);

    float vx;
    float vy;
    float angle;
    float max_speed;
    float thrust;

private:
    Camera* camera;
};

#endif /* MISSILE_H */
