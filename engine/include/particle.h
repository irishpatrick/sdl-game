#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdint>
#include "sprite.h"

class Animation;
class Texture;
class Timer;

class Particle: public Sprite
{
public:
    Particle();
    ~Particle();

    void SetLifeSpan(double);
    void update(float);
    void Reset();

private:
    double lifespan_;
    Timer* life_;
    Timer* clock_;
};

#endif /* PARTICLE_H */
