#ifndef PLAYER_H
#define PLAYER_H

#include <map>
#include <vector>
#include <string>
#include "engine.h"
#include "stats.h"

using namespace std;

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
