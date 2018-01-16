#ifndef TIMER_H
#define TIMER_H

#include <cstdint>
#include <SDL.h>

class Timer
{
public:
    Timer();
    ~Timer();

    void SetInterval(uint32_t);
    bool Tick();

private:
    uint32_t duration_;
    uint32_t then_;
    uint32_t now_;
};

#endif /* TIMER_H */