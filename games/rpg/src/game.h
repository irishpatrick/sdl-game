#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "groupmanager.h"
#include "player.h"
#include "door.h"
#include "stats.h"
#include "dialogue.h"
#include "npc.h"

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
    Npc monster;
    engine::Sprite background;
    engine::Sprite animtest;
    engine::Group stage;
    engine::Camera camera;
    GroupManager groups_;
    engine::Animation test;
    Door doortest;
    engine::OneShot op;
    engine::OneShot ol;
    vector<engine::Sprite*> hero_collisions;
    engine::ImageFont font;
    Dialogue dlg;
    //gui::List list;
};

#endif /* GAME_H */
