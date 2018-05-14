#include "gamepad.hpp"

namespace engine {

Gamepad::Gamepad()
{
    id_ = 0;
    instanceid_ = 0;
    pad_ = nullptr;
    joy_ = nullptr;
}

Gamepad::~Gamepad()
{

}

void Gamepad::Create(int id)
{
    id_ = id;

    if (SDL_IsGameController(id_))
    {
        pad_ = SDL_GameControllerOpen(id_);
        if (pad_)
        {
            joy_ = SDL_GameControllerGetJoystick(pad_);
            instanceid_ = SDL_JoystickInstanceID(joy_);
        }
    }
}

int Gamepad::GetId()
{
    return id_;
}

void Gamepad::Close()
{
    SDL_GameControllerClose(pad_);
}

}
