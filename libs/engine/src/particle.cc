#include "particle.h"
#include "animation.h"
#include "texture.h"
#include "timer.h"

namespace engine {

Particle::Particle(): Sprite()
{
    life_ = new Timer();
    clock_ = new Timer();
}

Particle::~Particle()
{
    delete life_;
}

void Particle::Reset()
{
    visible_ = true;
}

void Particle::SetLifeSpan(double  n)
{
    life_->SetInterval(n);
    life_->Reset();
}

void Particle::update(float delta)
{
    if (!visible_) return;

    if (life_->Tick())
    {
        visible_ = false;
        return;
    }

    if (clock_->Tick())
    {

    }
    x += xvel;
    y += yvel;
}

}
