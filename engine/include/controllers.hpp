#pragma once

#define MAX_CONTROLLERS 4

#include <SDL2/SDL.h>
#include "gamepad.hpp"

namespace engine {

class Controllers
{
public:

    static void ProcessEvent(const SDL_Event&);
    static int GetControllerIndex(SDL_JoystickID);
    static void CloseAll();

private:
    static Gamepad gamepads_[MAX_CONTROLLERS];
};

}
