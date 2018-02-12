#ifndef PLANE_H
#define PLANE_H

#include <cmath>
#include "engine.h"

class Plane: public Sprite
{
public:
    Plane();
    ~Plane();

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

#endif /* PLANE_H */
