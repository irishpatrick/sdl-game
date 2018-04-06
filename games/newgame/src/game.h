#ifndef GAME_H
#define GAME_H

#include <cstdint>
#include <vector>
#include "SDL2/SDL.h"

#include "engine.h"

using namespace std;

class Game: public engine::State {

public:
    Game(SDL_Renderer*);
    ~Game();

    void init() override;
    void update(float, const uint8_t*) override;
    void render() override;
    void destroy() override;

    engine::Sprite background;
    vector<engine::Sprite> white;
    vector<engine::Sprite> black;
};

#endif /* GAME_H */
