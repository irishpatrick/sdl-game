#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <future>

#include "groupmanager.h"
#include "state.h"
#include "assets.h"
#include "sprite.h"
#include "group.h"
#include "util.h"
#include "config.h"
#include "texture.h"
#include "light.h"
#include "animation.h"
#include "camera.h"
#include "door.h"

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
    Sprite hero;
    Door doortest;
    Sprite doorsprite;
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
};

#endif /* GAME_H */
