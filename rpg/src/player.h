#ifndef PLAYER_H
#define PLAYER_H

#include "engine.h"

class Player: public Sprite
{
public:
    Player();
    ~Player();

    LocationStack* getDoorStack();

private:
    LocationStack doorstack;
};

#endif /* PLAYER_H */
