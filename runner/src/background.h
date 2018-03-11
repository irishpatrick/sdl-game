#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <SDL2/SDL.h>
#include <engine.h>

using namespace std;

class Background {

public:
    Background();
    ~Background();

    void update(float);
    void draw(SDL_Renderer*);
    void setSpeed(float);

private:
    vector<engine::Sprite*> frames;
    float speed;
};

#endif /* BACKGROUND_H */
