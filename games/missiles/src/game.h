#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <vector>
#include "SDL2/SDL.h"
#include "engine.h"

class Plane;
class Missile;

class Game: public State
{
public:
    Game(SDL_Renderer*);
    ~Game();

    void init();
    void update(float, const uint8_t*);
    void render();
    void destroy();
    void setMousePos(int, int);

private:
    int mx;
    int my;
    float target_angle;
    Plane* bg;
    Plane* plane;
    Camera* camera;
    Timer* timer;
    std::vector<Missile*> missiles;
};

#endif /* GAME_H */