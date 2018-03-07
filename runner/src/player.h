#ifndef PLAYER_H
#define PLAYER_H

#include <engine.h>

class Player: public Sprite {

public:
    Player();
    ~Player();

    void update(float);
    void setGround(float);
    void jump(float);

private:
    float ground;
    float fall;
};

#endif /* PLAYER_H */
