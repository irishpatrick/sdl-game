#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <iostream>
#include <cmath>
#include <engine.h>

using namespace std;

class Player: public engine::Sprite {

public:
    Player();
    ~Player();

    void update(float);
    void setGround(float);
    void jump(float);

private:
    float ground;
    float fall;
    bool jumping;
    bool change;
    bool last;
    float t;
    float velocity;

    // physics
    float Fg;
    float Fn;
    float Ft;
    float Fa;
    float mass;
    float gravity;
    float vi;

};

#endif /* PLAYER_H */
