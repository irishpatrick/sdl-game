#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <iostream>
#include <cmath>
#include <engine.h>
#include "quadratic.h"
#include "sigmoid.h"

using namespace std;

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
    bool jumping;
    bool change;
    bool last;
    float t;
    float velocity;
    Quadratic path;
    Sigmoid grav;
    Sigmoid thrust;

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
