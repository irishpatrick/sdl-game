#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <SDL.h>

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

#endif /* GAMEPAD_H */