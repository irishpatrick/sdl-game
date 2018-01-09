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
    Assets assets;
    Sprite hero;
    Sprite monster;
    Sprite background;
    std::vector<Sprite*> grass;
    Group stage;
    Group testroom;
    Camera camera;
	GroupManager groups_;
};

#endif /* GAME_H */
