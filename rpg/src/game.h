#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <future>

#include "engine.h"
#include "groupmanager.h"
#include "door.h"
#include "config.h"
#include "player.h"

class Game: public State
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
    Sprite monster;
    Sprite background;
    Sprite animtest;
    std::vector<Sprite*> grass;
    Group stage;
    Group testroom;
    Camera camera;
    GroupManager groups_;
    Light light;
    Animation test;
    Door doortest;
    OneShot op;
    std::vector<Sprite*> hero_collisions;
};

#endif /* GAME_H */
