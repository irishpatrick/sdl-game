#include "Keyboard.hpp"
#include <iostream>

namespace engine
{
    const uint8_t* Keyboard::keys = nullptr;
    int Keyboard::primed = 0;
    uint8_t Keyboard::states[1000];

    void Keyboard::poll()
    {
        if (!primed)
        {
            primed = 1;
            memset(&states, 0, 1000);
        }
        keys = SDL_GetKeyboardState(nullptr);   
    }

    bool Keyboard::isDown(SDL_Scancode sc)
    {
        return keys[sc];
    }

    bool Keyboard::isPressed(SDL_Scancode sc)
    {
        if (keys[sc] && !states[sc])
        {
            states[sc] = 1;
            return true;
        }
        else if (keys[sc] && states[sc])
        {
            return false;
        }
        else if (!keys[sc] && states[sc])
        {
            states[sc] = 0;
            return false;
        }
        return false;
    }

    bool Keyboard::isDown(const char* key)
    {
        return isDown(SDL_GetScancodeFromName(key));
    }

    bool Keyboard::isPressed(const char* key)
    {
        return isPressed(SDL_GetScancodeFromName(key));
    }
}