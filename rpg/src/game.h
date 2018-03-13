#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <future>
#include <engine.h>

#include "config.h"
#include "groupmanager.h"
#include "player.h"
#include "door.h"

using namespace std;

class Game: public engine::State
{
public:
    Game(SDL_Renderer*);
    ~Game();

    void init();
    void tests();
    void update(float, const uint8_t*);
    void render();
    void destroy();

private:
    Player hero;
    engine::Sprite monster;
    engine::Sprite background;
    engine::Sprite animtest;
    vector<engine::Sprite*> grass;
    engine::Group stage;
    engine::Group testroom;
    engine::Camera camera;
    GroupManager groups_;
    engine::Light light;
    engine::Animation test;
    Door doortest;
    engine::OneShot op;
    vector<engine::Sprite*> hero_collisions;
};

#endif /* GAME_H */
