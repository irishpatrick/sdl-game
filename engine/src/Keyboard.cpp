#include "Keyboard.hpp"
#include <iostream>

namespace engine
{
    const uint8_t* Keyboard::keys = nullptr;
    int Keyboard::primed = 0;
    uint8_t Keyboard::states[1000];
    std::stack<int> Keyboard::locks = std::stack<int>();

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

    int Keyboard::lock()
    {
        int id = locks.size();
        locks.push(id);
        return id;
    }

    int Keyboard::unlock(int id)
    {
        if (id != locks.top())
        {
            return -1;
        }
        locks.pop();
        return id;
    }

    int Keyboard::lockDepth()
    {
        return locks.size();
    }

    bool Keyboard::isLocked()
    {
        return locks.size() > 0;
    }
}