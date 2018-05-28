#pragma once

#include <cstdint>
#include <SDL2/SDL.h>

#include "context.hpp"

namespace engine {

class State
{
public:
    State(Context*);
    virtual ~State();

    virtual void init();
    virtual void update(float, const uint8_t*);
    virtual void render();

    virtual void destroy();

protected:
    Context* ctx;
};

}
