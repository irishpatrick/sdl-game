#ifndef STATE_H
#define STATE_H

#include <cstdint>
#include <SDL2/SDL.h>

namespace engine {

class State
{
public:
    State(SDL_Renderer*);
    virtual ~State();

    virtual void init();
    virtual void update(float, const uint8_t*);
    virtual void render();

    virtual void destroy();

protected:
    SDL_Renderer* renderer;
};

}

#endif /* STATE_H */
