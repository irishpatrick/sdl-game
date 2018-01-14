#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#define MAX_CONTROLLERS 4

#include <SDL.h>
#include "gamepad.h"

class Controllers
{
public:

    static void ProcessEvent(const SDL_Event&);
    static int GetControllerIndex(SDL_JoystickID);
    static void CloseAll();

private:
    static Gamepad gamepads_[MAX_CONTROLLERS];
};

#endif /* CONTROLLERS_H */