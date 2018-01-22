#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdint>

class Animation;
class Texture;

class Particle
{
public:
    Particle();
    ~Particle();

    float x;
    float y;
    uint32_t w;
    uint32_t h;
private:
    Animation* anim_;
    Texture* tex_;
};

#endif /* PARTICLE_H */
