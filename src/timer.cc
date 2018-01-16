#include "timer.h"

Timer::Timer()
{
    duration_ = 0;
    then_ = 0;
    now_ = 0;
}

Timer::~Timer()
{

}

void Timer::SetInterval(uint32_t ms)
{
    duration_ = ms;
    then_ = SDL_GetTicks();
}

bool Timer::Tick()
{
    now_ = SDL_GetTicks();
    uint32_t delta = now_ - then_;
    if (delta >= duration_)
    {
        then_ = now_;
        return true;
    }
    return false;
}