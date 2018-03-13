#include "controllers.h"

namespace engine {

Gamepad Controllers::gamepads_[MAX_CONTROLLERS];

int Controllers::GetControllerIndex(SDL_JoystickID instance)
{
    for (int i=0; i < MAX_CONTROLLERS; i++)
    {
        if (gamepads_[i].GetId() == instance)
        {
            return i;
        }
    }
    return -1; // not found
}

void Controllers::ProcessEvent(const SDL_Event& e)
{
    switch (e.type)
    {
        case SDL_CONTROLLERDEVICEADDED:
        {
            if (e.cdevice.which < MAX_CONTROLLERS)
            {
                Gamepad& pad = gamepads_[e.cdevice.which];
                pad.Create(e.cdevice.which);
            }
            break;
        }
        case SDL_CONTROLLERDEVICEREMOVED:
        {
            int cIndex = GetControllerIndex(e.cdevice.which);
            if (cIndex < 0 ) break;
            Gamepad& pad = gamepads_[cIndex];
            pad.Close();
            break;
        }
    }
}

void Controllers::CloseAll()
{
    for (auto& e : gamepads_)
    {
        e.Close();
    }
}

}
