#ifndef PLAYER_H
#define PLAYER_H

#include <engine.h>

#include "stats.h"

class Player: public engine::Sprite
{
public:
    Player();
    ~Player();

    engine::LocationStack* getDoorStack();

private:
    engine::LocationStack doorstack;
    Stats stats;
};

#endif /* PLAYER_H */
