#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "state.h"

class Plane;

class Game: public State
{
public:
    Game(SDL_Renderer*);
    ~Game();

    void init();
    void update(float, const uint8_t*);
    void render();
    void destroy();

private:
    Plane* plane;
};

#endif /* GAME_H */
