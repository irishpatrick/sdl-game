#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <engine.h>
#include <nlohmann/json.hpp>

#include "player.h"
#include "floor.h"

using namespace std;
using json = nlohmann::json;

class Game: public engine::State {
public:
    Game(engine::Context*);
    ~Game();

    void init();
    void update(float, const uint8_t*);
    void render();
    void destroy();

private:
    json config;
    Player player;
    GridSprite bg;
    Floor f;
    engine::Camera camera;
    engine::Group stage;
};

#endif /* GAME_H */
