#include "Clock.hpp"
#include <SDL.h>
#include <iostream>

namespace engine
{
    Clock::~Clock()
    {

    }

    void Clock::start()
    {
        prev = SDL_GetTicks();
        lag = 0.0;
    }

    void Clock::tick()
    {
        cur = SDL_GetTicks();
        elapsed = cur - prev;
        prev = cur;
        lag += elapsed;
    }

    void Clock::lagTick()
    {
        lag -= updateInterval;
    }

    double Clock::getDelta()
    {
        return elapsed;
    }

    double Clock::getLag()
    {
        return lag;
    }

    double Clock::extrapolate()
    {
        double e = lag / updateInterval;
        if (e < 0.0 || e > 1.0)
        {
            std::cout << "bad value\n";
            e = 0.5;
        }
        return e;
    }

    bool Clock::hasLag()
    {
        return lag >= updateInterval;
    }
}
