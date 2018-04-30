#pragma once

#include <iostream>
#include <map>
#include <cstdlib>
#include <ctime>
#include <engine.h>

#include "gridsprite.h"

using namespace std;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Room;

class Floor: public GridSprite {
public:
    Floor();
    ~Floor();

    void generate(int);

    // overriden functions
    void velocityUpdate(float);
    void draw(SDL_Renderer*);
    void printMap();

private:
    //map<int, int> grid;
    Room* rooms;
    int nrooms;
    int world;
    SDL_Texture* t;
};
