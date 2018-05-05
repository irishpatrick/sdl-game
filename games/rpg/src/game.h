#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "groupmanager.h"
#include "player.h"
#include "door.h"
#include "stats.h"

#include <engine.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <future>

//#include "gui.h"

using namespace std;

class Game: public engine::State {
 public:
    Game(engine::Context*);
    ~Game();

    void init() override;
    void tests();
    void update(float, const uint8_t*) override;
    void render() override;
    void destroy() override;

 private:
    Player hero;
    engine::Sprite monster;
    engine::Sprite background;
    engine::Sprite animtest;
    vector<engine::Sprite*> grass;
    engine::Group stage;
    engine::Camera camera;
    GroupManager groups_;
    engine::Animation test;
    Door doortest;
    engine::OneShot op;
    vector<engine::Sprite*> hero_collisions;
    engine::ImageFont font;
    //gui::List list;
};

#endif /* GAME_H */
