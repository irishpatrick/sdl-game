#ifndef PLAYER_H
#define PLAYER_H

#include <engine.h>

class Player: public engine::Sprite
{
public:
    Player();
    ~Player();

    engine::LocationStack* getDoorStack();

private:
    engine::LocationStack doorstack;
};

#endif /* PLAYER_H */
