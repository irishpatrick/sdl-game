#pragma once

#include <SDL.h>
#include <cstdint>
#include "Context.hpp"

namespace engine
{
    class Canvas
    {
    public:
        Canvas() : texture(nullptr), surface(nullptr) {}
        ~Canvas()
        {
            if (surface != nullptr)
            {
                SDL_FreeSurface(surface);
            }
            if (texture != nullptr)
            {
                SDL_DestroyTexture(texture);
            }
        }
        
        void create(Context&, uint32_t, uint32_t);

    private:
        SDL_Texture* texture;
        SDL_Surface* surface;
    };
}