#include "particle.h"
#include "animation.h"
#include "texture.h"
#include "timer.h"

Particle::Particle(): Sprite()
{
    timer_ = new Timer();
}

Particle::~Particle()
{
    delete timer_;
}

void Particle::SetLifeSpan(double  n)
{
    timer_->SetInterval(n);
}

void Particle::update(float delta)
{
    if (timer_->Tick())
    {

    }
}
