#pragma once

#include <SDL.h>
#include <cstdint>

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

    private:
        static int primed;
        static const uint8_t* keys;
        static uint8_t states[1000];
    };
}