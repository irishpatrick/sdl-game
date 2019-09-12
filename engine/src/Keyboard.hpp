#pragma once

#include <SDL.h>
#include <cstdint>
#include <stack>

namespace engine
{
    class Keyboard
    {
    public:
        static void poll();
        static bool isDown(SDL_Scancode);
        static bool isPressed(SDL_Scancode);
        static bool isDown(const char*);
        static bool isPressed(const char*);

        static int lock();
        static int unlock(int);
        static bool isLocked();
        static int lockDepth();

    private:
        static int primed;
        static const uint8_t* keys;
        static uint8_t states[1000];
        static std::stack<int> locks;
    };
}