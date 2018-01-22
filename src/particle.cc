#include "particle.h"
#include "animation.h"
#include "texture.h"

Particle::Particle()
{
    x = 0;
    y = 0;
    w = 0;
    h = 0;
    anim_ = new Animation();
    tex_ = nullptr;
}

Particle::~Particle()
{
    delete anim_;
}
