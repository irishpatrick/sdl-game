#pragma once

#include <SDL2/SDL.h>

namespace engine {

class Gamepad
{
public:
    Gamepad();
    ~Gamepad();

    void Create(int);
    void Close();
    int GetId();

private:
    int id_;
    int instanceid_;
    SDL_GameController* pad_;
    SDL_Joystick* joy_;

};

}