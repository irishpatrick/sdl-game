#ifndef GAME_H
#define GAME_H

#include <string>
#include <cstdint>
#include <engine.h>

class Player;
class Background;

class Game: public State {

public:
    Game(SDL_Renderer*);
    ~Game();

    void init();
    void update(float, const uint8_t*);
    void render();

private:
    Player* player;
    Background* background;
};

#endif /* GAME_H */
