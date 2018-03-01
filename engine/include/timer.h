#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <SDL2/SDL.h>

class Timer
{
public:
    Timer();
    ~Timer();

    void SetInterval(double);
    void Reset();
    bool Tick();

private:
    double duration_;
    uint32_t then_;
    uint32_t now_;
};

#endif /* TIMER_H */
